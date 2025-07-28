//
// Created by Женя on 20.06.2025.
//

#include "regulatory_state_provider.hpp"


#include "../../regulatory.hpp"


MapStyle RegulatoryStateProvider::mapStyle(ISubscriber * subscriber, const QString & styleName)
{
    const auto regulatory = dynamic_cast<Regulatory *>(subscriber);

    return regulatory->m_styles.value( styleName );
}

MapStyle RegulatoryStateProvider::buildingsStyle(ISubscriber * subscriber, const QString & styleName)
{
    const auto regulatory = dynamic_cast<Regulatory *>(subscriber);

    return regulatory->m_buildings.value( styleName );
}
