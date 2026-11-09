"""Accessible doorbell notification state machine with rate limiting."""
from math import isfinite

class Doorbell:
    def __init__(self, debounce_seconds=0.3, quiet_start=22, quiet_end=7):
        if type(debounce_seconds) not in (int, float) or not isfinite(debounce_seconds) or debounce_seconds < 0:
            raise ValueError("invalid debounce")
        if type(quiet_start) is not int or type(quiet_end) is not int or not 0 <= quiet_start <= 23 or not 0 <= quiet_end <= 23:
            raise ValueError("quiet hours must be integers 0..23")
        self.debounce_seconds = debounce_seconds
        self.quiet_start = quiet_start
        self.quiet_end = quiet_end
        self.last_press = None

    def _quiet(self, hour):
        if self.quiet_start == self.quiet_end:
            return False
        if self.quiet_start < self.quiet_end:
            return self.quiet_start <= hour < self.quiet_end
        return hour >= self.quiet_start or hour < self.quiet_end

    def press(self, timestamp, local_hour):
        if type(timestamp) not in (int, float) or not isfinite(timestamp) or timestamp < 0:
            raise ValueError("invalid timestamp")
        if type(local_hour) is not int or not 0 <= local_hour <= 23:
            raise ValueError("invalid hour")
        if self.last_press is not None and timestamp < self.last_press:
            raise ValueError("timestamps must not decrease")
        if self.last_press is not None and timestamp - self.last_press < self.debounce_seconds:
            return {"accepted": False, "reason": "debounced", "visual": False,
                    "haptic": False, "audio": False}
        self.last_press = timestamp
        return {"accepted": True, "reason": "quiet_hours" if self._quiet(local_hour) else "ring",
                "visual": True, "haptic": True, "audio": not self._quiet(local_hour)}
