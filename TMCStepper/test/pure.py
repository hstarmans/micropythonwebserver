import unittest
from gpiozero import MCP3008


class MotorTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        clock_pin = 21
        mosi_pin = 20
        miso_pin = 19
        select_pin = 7
        cls.dev = MCP3008(channel=0,
                          mosi_pin=mosi_pin,
                          miso_pin=miso_pin,
                          select_pin=select_pin,
                          clock_pin=clock_pin)
        # spidev method stopped working
        # cls.spi = spidev.SpiDev()
        # cls.spi.open(1, 0)
        # cls.spi.max_speed_hz = int(16000000/8)

    def test_simple(self):
        '''write to chopconfig and verify data is returned

        see example on page 22
        https://www.trinamic.com/fileadmin/assets/Products/ICs_Documents/TMC2130_datasheet.pdf
        If more than 40 bits are sent, only the last 40 bits received before
        the rising edge of CSN are recognized as the command.
        The rest are shifted on in the ring.
        There are three drivers in the ring.
        '''
        lst = [0XEC, 1, 2, 3, 4]*3  # 0XEC = 236, i.e. data is altered
        expected = [249, 1, 2, 3, 4]*3
        for _ in range(2):
            self.dev._spi.write(lst)
            res = self.dev._spi.read(len(lst))
            print(res)
        self.assertEqual(expected, res)


if __name__ == '__main__':
    unittest.main()
