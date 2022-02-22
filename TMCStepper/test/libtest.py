import unittest
import steppers
from gpiozero import LED


class MotorTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        # load linked motors
        cls.motors = [steppers.TMC2130(link_index=i) for i in range(1, 4)]
        steppers.bcm2835_init()
        cls.enable = LED(17)

    def test_simple(self):
        ''' write to all the motors
        '''
        steppers.bcm2835_init()
        for motor in self.motors:
            motor.begin()
            motor.toff(5)
            # ideally should be 0
            # on working equipment it is always 2
            self.assertEqual(motor.test_connection(), 2)
            motor.rms_current(600)
            motor.microsteps(16)
            motor.en_pwm_mode(True)
        # close bcm2835
        steppers.bcm2835_close()
        print("Motors should be blocked now, check by hand \
              press enter to exit")
        self.enable.off()
        input()


if __name__ == '__main__':
    unittest.main()
