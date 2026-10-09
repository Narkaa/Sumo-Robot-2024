# Bukhuu — Autonomous Mega Sumo Robot

🥈 **2nd place, Mega Sumo category — RobotChallenge 2022 (China)**
Competed against teams from Thailand, China, and Mongolia.

<!-- Add a photo of the robot here, e.g.:
![Bukhuu sumo robot](docs/robot.jpg) -->

Bukhuu is an autonomous Mega Sumo robot. Its firmware is written in C for a Microchip
dsPIC30F microcontroller. The robot waits for the referee's start signal, runs an opening
strategy chosen before the match, then steers toward the opponent with five opponent sensors.
When an edge sensor sees the ring border, it backs away from it.

## Hardware

| Component | Details |
|---|---|
| Microcontroller | Microchip dsPIC30F (project targets the **dsPIC30F6015**), 80 MHz oscillator (XT × 8 PLL), 20 MIPS |
| Opponent sensors | 5 digital sensors: two on the sides, two front diagonals, one in the center |
| Edge sensors | 2 line sensors that detect the white ring border |
| Drive | 2 motor channels, each with a direction pin and PWM from an output-compare module |
| Start | Input for the competition start/stop module |
| User interface | 2 buttons to pick the strategy and toggle delayed start; 12 status LEDs |

## Firmware architecture

```
Timer4 ISR  (every 400 µs)
 ├─ motor_control()   ramp each motor toward its target power, set direction + PWM duty
 ├─ multiplex 12 LEDs (4 select lines × 3 LED lines)
 └─ kick the watchdog, flag the main loop

Main loop  (runs once per tick)
 ├─ read buttons (debounced)         → choose strategy / delayed start
 ├─ read_s()     opponent sensors     → debounce counters
 ├─ line_sens()  edge sensors         → debounce counters
 ├─ strategy state machine            → target power for each motor
 ├─ sensor steering                   → turn toward a detected opponent
 └─ control()    edge escape + start-signal gating
```

### Key techniques

- **Timer-driven real-time control.** The control loop runs at a fixed 400 µs period from a hardware timer interrupt, which keeps timing deterministic. PWM runs at 10 kHz (Timer2).
- **Acceleration ramping.** Motor power moves toward its target in small steps on every tick instead of jumping. This limits current spikes and wheel slip.
- **Sensor debouncing.** A sensor counts as triggered only after several consecutive positive reads, which filters out noise and reflections.
- **Opponent tracking.** If a side sensor sees the opponent, the motor on that side stops so the robot spins toward it. A diagonal sensor scales that motor's power to about 2/3 for a gentler turn. The center sensor equalizes both motors so the robot drives straight in.
- **Edge escape.** When an edge sensor triggers, the robot brakes, reverses, brakes again, and spins away from the side that hit the line, then resumes.
- **Safety.** Both motors are forced to zero whenever the start-module signal is off. The watchdog timer resets the MCU if the loop ever hangs.

## Opening strategies

The strategy is chosen with button 1 before the match and shown on the status LEDs.

| Mode | Strategy |
|---|---|
| 0 | **Head-on charge.** Full power forward, with sensor steering. |
| 1 / 2 | **Pivot and ambush** (mirror images). Pivot, reverse, then wait until a sensor sees the opponent (or a timeout), then charge. |
| 3 / 4 | **Flanking arc** (mirror images). Arc out to one side, drive forward, turn back in, then attack. |

Button 2 toggles a **delayed start** (about 6 s) before the selected strategy begins.

## Repository layout

| File | Purpose |
|---|---|
| `bukhuu sumo.c` | Main firmware: control loop, sensors, strategies, motor control |
| `bukhuu sumo.h` | Device configuration, fuses, clock, pin and register mapping |
| `gyro.c` | MPU-6050 gyroscope driver over I²C. Included but **disabled** in the competition build. |
| `ESP12.c` | ESP-12 (ESP8266) Wi-Fi driver over UART using AT commands. Experimental, not part of the competition build. |
| `mode.c`, `function.c` | Movement and sensor routines from earlier robot versions. Kept for reference, not compiled into this build. |

## Building

- **Compiler:** CCS C Compiler for dsPIC (PCD) v5.048
- Compile `bukhuu sumo.c` with the dsPIC30F6015 target. The compiler produces `bukhuu sumo.hex`, which you flash over ICSP (for example with a PICkit).
