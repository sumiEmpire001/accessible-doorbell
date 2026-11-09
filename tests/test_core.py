import unittest
from accessible_doorbell import Doorbell

class DoorbellTests(unittest.TestCase):
    def test_accessible_notifications(self):
        d = Doorbell()
        self.assertEqual(d.press(1, 12)["audio"], True)
        self.assertFalse(d.press(1.1, 12)["accepted"])
        quiet = d.press(2, 23)
        self.assertTrue(quiet["visual"])
        self.assertTrue(quiet["haptic"])
        self.assertFalse(quiet["audio"])
        self.assertFalse(d.press(3, 6)["audio"])
        self.assertTrue(d.press(4, 7)["audio"])
    def test_validation_and_nonwrapping_hours(self):
        d = Doorbell(quiet_start=10, quiet_end=12)
        self.assertFalse(d.press(0, 11)["audio"])
        self.assertTrue(d.press(1, 13)["audio"])
        with self.assertRaises(ValueError):
            d.press(0.5, 14)
        with self.assertRaises(ValueError):
            d.press(2, 24)
        with self.assertRaises(ValueError):
            Doorbell(debounce_seconds=-1)
