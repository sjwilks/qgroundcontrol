/*=====================================================================
 
 QGroundControl Open Source Ground Control Station
 
 (c) 2009 - 2014 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 
 This file is part of the QGROUNDCONTROL project
 
 QGROUNDCONTROL is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 QGROUNDCONTROL is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with QGROUNDCONTROL. If not, see <http://www.gnu.org/licenses/>.
 
 ======================================================================*/

/// @file
///     @author Don Gagne <don@thegagnes.com>

#include "GenericAutoPilotPlugin.h"

GenericAutoPilotPlugin::GenericAutoPilotPlugin(QObject* parent) :
    AutoPilotPlugin(parent)
{
    
}

QList<VehicleComponent*> GenericAutoPilotPlugin::getVehicleComponents(UASInterface* uas) const
{
    Q_UNUSED(uas);
    
    // Generic autopilot has no configurable components
    return QList<VehicleComponent*>();
}

QList<AutoPilotPlugin::FullMode_t> GenericAutoPilotPlugin::getModes(void) const
{
    QList<FullMode_t>       modeList;
    FullMode_t              fullMode;

    fullMode.customMode = 0;
    
    fullMode.baseMode = MAV_MODE_FLAG_MANUAL_INPUT_ENABLED;
    modeList << fullMode;
    
    fullMode.baseMode = MAV_MODE_FLAG_MANUAL_INPUT_ENABLED | MAV_MODE_FLAG_STABILIZE_ENABLED;
    modeList << fullMode;
    
    fullMode.baseMode = MAV_MODE_FLAG_MANUAL_INPUT_ENABLED | MAV_MODE_FLAG_STABILIZE_ENABLED | MAV_MODE_FLAG_GUIDED_ENABLED;
    modeList << fullMode;

    fullMode.baseMode = MAV_MODE_FLAG_AUTO_ENABLED | MAV_MODE_FLAG_STABILIZE_ENABLED | MAV_MODE_FLAG_GUIDED_ENABLED;
    modeList << fullMode;
    
    return modeList;
}

QString GenericAutoPilotPlugin::getShortModeText(uint8_t baseMode, uint32_t customMode) const
{
    Q_UNUSED(customMode);
    
    QString mode;
    
    // use base_mode - not autopilot-specific
    if (baseMode == 0) {
        mode = "|PREFLIGHT";
    } else if (baseMode & MAV_MODE_FLAG_DECODE_POSITION_AUTO) {
        mode = "|AUTO";
    } else if (baseMode & MAV_MODE_FLAG_DECODE_POSITION_MANUAL) {
        mode = "|MANUAL";
        if (baseMode & MAV_MODE_FLAG_DECODE_POSITION_GUIDED) {
            mode += "|GUIDED";
        } else if (baseMode & MAV_MODE_FLAG_DECODE_POSITION_STABILIZE) {
            mode += "|STABILIZED";
        }
    }
    
    return mode;
}

