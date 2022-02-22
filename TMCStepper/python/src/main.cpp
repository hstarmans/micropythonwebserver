#include <pybind11/pybind11.h>
#include <TMCStepper.h>

#define CS_PIN           RPI_BPLUS_GPIO_J8_26  // Chip select                         GPIO7
#define SW_MOSI          RPI_BPLUS_GPIO_J8_38  // Software Master Out Slave In (MOSI) GPIO20
#define SW_MISO          RPI_BPLUS_GPIO_J8_35  // Software Master In Slave Out (MISO) GPIO19
#define SW_SCK           RPI_BPLUS_GPIO_J8_40  // Software Slave Clock (SCK)          GPIO21


namespace py = pybind11;

uint16_t cs = CS_PIN;
uint16_t mosi = SW_MOSI;
uint16_t miso = SW_MISO;
uint16_t sck = SW_SCK;

PYBIND11_MODULE(steppers, m) {
    m.def("bcm2835_init", &bcm2835_init);
    m.def("bcm2835_close", &bcm2835_close);
    py::class_<TMC2130Stepper>(m, "TMC2130")
        //.def(py::init<uint16_t, float, int8_t>(), py::arg("pinCS"), py::arg("RS")=0.11, py::arg("link_index"))
        .def(py::init<uint16_t, float, uint16_t, uint16_t, uint16_t, int8_t>(), py::arg("pinCS")=cs, py::arg("RS")=0.11,
             py::arg("pinMOSI")=mosi, py::arg("pinMISO")=miso, py::arg("pinSCK")=sck, py::arg("link_index")=-1)
        .def("begin", &TMC2130Stepper::begin)
        .def("test_connection", &TMC2130Stepper::test_connection)
        .def("toff", py::overload_cast<uint8_t>(&TMC2130Stepper::toff), "Set the toff time")
        .def("microsteps", py::overload_cast<uint16_t>(&TMC2130Stepper::microsteps))
        .def("rms_current", py::overload_cast<uint16_t>(&TMC2130Stepper::rms_current), "Set the max RMS current in mili ampere", py::arg("mA"))
        .def("en_pwm_mode", py::overload_cast<bool>(&TMC2130Stepper::en_pwm_mode), "Toggle stealthChop on TMC2130", py::arg("stealthchop"));
}