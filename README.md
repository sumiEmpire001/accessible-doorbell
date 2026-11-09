# accessible-doorbell

A doorbell event-processing prototype that produces visual, haptic, and audio notification flags, suppresses rapid duplicate presses, and supports configurable quiet hours (including overnight ranges). The caller supplies local hour; no hardware, time-zone handling, mobile push notifications, or accessibility certification is included.

## Run tests

Requires Python 3.10+ with no external dependencies.

```bash
python -m unittest discover -s tests -v
```

## Example

```python
from accessible_doorbell import Doorbell
bell = Doorbell()
print(bell.press(1.0, 23))
```

GitHub Actions runs the test suite on Python 3.10, 3.12, and 3.13. Real hardware integration and deployment remain future work.

## C++ Arduino / ESP32 implementation

The Python state machine is preserved. The C++11 equivalent in
`arduino/AccessibleDoorbell/src/AccessibleDoorbell.h` validates timestamps,
debounces presses, handles quiet hours across midnight, and returns separate
visual, haptic and audio recommendation flags.

The `IndicatorDemo` Arduino sketch uses a button plus three **LEDs** to
demonstrate these flags. No vibration motor or speaker is connected. Clock hours
are intentionally simulated (one hour every 10 seconds); add a real RTC or
trusted network time before actual scheduling. Pin map: Uno D2 button,
D8-D10 LEDs; classic ESP32 GPIO27 button, GPIO18/19/21 LEDs.

Run portable C++ tests:
```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```
GitHub Actions compiles C++ with GCC/Clang and attempts both Arduino Uno and
ESP32 sketch builds. Real motor/buzzer interfaces, accessible-user testing,
timekeeping, power behavior and hardware reliability remain unverified.
