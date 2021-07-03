#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "FEBDTP.hxx"

namespace py = pybind11;

// This class has a user defined struct in
// the class definition.
// A reference:
// https://stackoverflow.com/questions/48372537/pybind11-for-c-code-with-inner-struct-created-via-static-factory-method
PYBIND11_MODULE(protocol, m) {
    m.doc() = "CAEN DT5702 protocol module"; // optional module docstring
    py::class_<FEBDTP_PKT>(m, "FEBDTP_PKT")
        .def_readwrite("Data", &FEBDTP_PKT::Data); // make data field accessible
    py::class_<FEBDTP>(m, "FEBDTP")
        .def_readwrite("dstmac", &FEBDTP::dstmac) // make destination MAC address accessible
        .def_readwrite("fPacketHandler", &FEBDTP::fPacketHandler) // make function pointer accessible
        .def_readwrite("gpkt", &FEBDTP::gpkt) // make packet accessible
        .def_readwrite("macs", &FEBDTP::macs) // make macs readable 
        .def_readwrite("nclients", &FEBDTP::nclients) // make nclients readable 
        .def_readwrite("VCXO", &FEBDTP::VCXO) // make VCXO writable
        .def(py::init<>())
        .def(py::init<const char *>())
        .def("Init", &FEBDTP::Init)
        .def("Init_FEBDTP_pkt", static_cast<void (FEBDTP::*)(FEBDTP_PKT *)>(&FEBDTP::Init_FEBDTP_pkt))
        .def("PrintMacTable", &FEBDTP::PrintMacTable)
        .def("ScanClients", &FEBDTP::ScanClients)
        .def("setPacketHandler", &FEBDTP::setPacketHandler);
}