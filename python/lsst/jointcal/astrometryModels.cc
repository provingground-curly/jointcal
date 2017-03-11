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

#include "lsst/jointcal/CcdImage.h"
#include "lsst/jointcal/DistortionModel.h"
#include "lsst/jointcal/SimplePolyModel.h"
#include "lsst/jointcal/ConstrainedPolyModel.h"

namespace py = pybind11;
using namespace pybind11::literals;

namespace lsst {
namespace jointcal {
namespace {

void declareDistortionModel(py::module &mod) {
    py::class_<DistortionModel, std::shared_ptr<DistortionModel>> cls(mod, "DistortionModel");

    cls.def("produceSipWcs", &SimplePolyModel::produceSipWcs);
}

void declareSimplePolyModel(py::module &mod) {
    py::class_<SimplePolyModel, std::shared_ptr<SimplePolyModel>, DistortionModel> cls(mod, "SimplePolyModel");

    cls.def(py::init<CcdImageList const&, const ProjectionHandler *, bool, unsigned, unsigned>(),
            "ccdImageList"_a, "projectionHandler"_a, "initFromWcs"_a, "nNotFit"_a=0, "degree"_a=3);
}

void declareConstrainedPolyModel(py::module &mod) {
    py::class_<ConstrainedPolyModel, std::shared_ptr<ConstrainedPolyModel>, DistortionModel> cls(mod, "ConstrainedPolyModel");

    cls.def(py::init<CcdImageList const&, const ProjectionHandler *, bool, unsigned>(),
            "ccdImageList"_a, "projectionHandler"_a, "initFromWcs"_a, "nNotFit"_a=0);
}

PYBIND11_PLUGIN(astrometryModels) {
    py::module::import("lsst.jointcal.gtransfo"); // for produceSipWcs return value
    py::module mod("astrometryModels");

    declareDistortionModel(mod);
    declareSimplePolyModel(mod);
    declareConstrainedPolyModel(mod);

    return mod.ptr();
}

}}}  // lsst::jointcal::<anonymous>
