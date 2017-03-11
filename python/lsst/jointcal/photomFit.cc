/*
 * LSST Data Management System
 *
 * This product includes software developed by the
 * LSST Project (http://www.lsst.org/).
 * See the COPYRIGHT file
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the LSST License Statement and
 * the GNU General Public License along with this program.  If not,
 * see <https://www.lsstcorp.org/LegalNotices/>.
 */

#include "pybind11/pybind11.h"

#include "lsst/jointcal/Chi2.h"
#include "lsst/jointcal/Associations.h"
#include "lsst/jointcal/PhotomFit.h"
#include "lsst/jointcal/PhotomModel.h"

namespace py = pybind11;
using namespace pybind11::literals;

namespace lsst {
namespace jointcal {
namespace {

void declarePhotomFit(py::module &mod) {
    py::class_<PhotomFit, std::shared_ptr<PhotomFit>> cls(mod, "PhotomFit");

    cls.def(py::init<Associations &, PhotomModel *, double>(),
            "associations"_a, "photomModel"_a, "fluxError"_a);

    cls.def("minimize", &PhotomFit::minimize, "whatToFit"_a);
    cls.def("computeChi2", &PhotomFit::computeChi2);
    cls.def("makeResTuple", &PhotomFit::makeResTuple);
}

PYBIND11_PLUGIN(photomFit) {
    py::module::import("lsst.jointcal.chi2"); // need this for computeChi2's return value
    py::module mod("photomFit");

    declarePhotomFit(mod);

    return mod.ptr();
}

}}}  // lsst::jointcal::<anonymous>
