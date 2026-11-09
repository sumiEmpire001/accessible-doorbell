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
