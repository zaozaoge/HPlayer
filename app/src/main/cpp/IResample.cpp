//
// Created by 胡章孝 on 2019/5/13.
//

#include "IResample.h"

void IResample::Update(XData xData) {
    XData d = this->Resample(xData);
    if (d.size > 0) {
        this->Notify(d);
    }
}
