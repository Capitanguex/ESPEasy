#include "_Plugin_Helper.h"
#ifdef USES_P033

// #######################################################################################################
// #################################### Plugin 033: Dummy ################################################
// #######################################################################################################

# define PLUGIN_033
# define PLUGIN_ID_033         33
# define PLUGIN_NAME_033       "Generic - Dummy Device"
# define PLUGIN_VALUENAME1_033 "Dummy"
boolean Plugin_033(uint8_t function, struct EventStruct *event, String& string)
{
  boolean success = false;

  switch (function)
  {
    case PLUGIN_DEVICE_ADD:
    {
      Device[++deviceCount].Number           = PLUGIN_ID_033;
      Device[deviceCount].Type               = DEVICE_TYPE_DUMMY;
      Device[deviceCount].VType              = Sensor_VType::SENSOR_TYPE_SINGLE;
      Device[deviceCount].Ports              = 0;
      Device[deviceCount].PullUpOption       = false;
      Device[deviceCount].InverseLogicOption = false;
      Device[deviceCount].FormulaOption      = false;
      Device[deviceCount].DecimalsOnly       = true;
      Device[deviceCount].ValueCount         = 4;
      Device[deviceCount].SendDataOption     = true;
      Device[deviceCount].TimerOption        = true;
      Device[deviceCount].TimerOptional      = true;
      Device[deviceCount].GlobalSyncOption   = true;
      Device[deviceCount].OutputDataType     = Output_Data_type_t::All;
      Device[deviceCount].PluginStats        = true;
      break;
    }

    case PLUGIN_GET_DEVICENAME:
    {
      string = F(PLUGIN_NAME_033);
      break;
    }

    case PLUGIN_GET_DEVICEVALUENAMES:
    {
      // FIXME TD-er: Copy names as done in P026_Sysinfo.ino.
      strcpy_P(ExtraTaskSettings.TaskDeviceValueNames[0], PSTR(PLUGIN_VALUENAME1_033));
      const Sensor_VType sensorType = static_cast<Sensor_VType>(PCONFIG(0));

      if (isIntegerOutputDataType(sensorType)) {
        for (uint8_t i = 0; i < VARS_PER_TASK; ++i) {
          ExtraTaskSettings.TaskDeviceValueDecimals[i] = 0;
        }
      }
      break;
    }

    case PLUGIN_GET_DEVICEVALUECOUNT:
    {
      event->Par1 = getValueCountFromSensorType(static_cast<Sensor_VType>(PCONFIG(0)));
      success     = true;
      break;
    }

    case PLUGIN_GET_DEVICEVTYPE:
    {
      event->sensorType = static_cast<Sensor_VType>(PCONFIG(0));
      event->idx        = 0;
      success           = true;
      break;
    }

    case PLUGIN_INIT:
    {
      success = true;
      break;
    }

    case PLUGIN_READ:
    {
      event->sensorType = static_cast<Sensor_VType>(PCONFIG(0));
      # ifndef LIMIT_BUILD_SIZE

      if (loglevelActiveFor(LOG_LEVEL_INFO)) {
        const uint8_t valueCount =
          getValueCountFromSensorType(static_cast<Sensor_VType>(PCONFIG(0)));

        for (uint8_t x = 0; x < valueCount; ++x)
        {
          addLog(LOG_LEVEL_INFO,
                 strformat(F("Dummy: value %d: %s"), x + 1, formatUserVarNoCheck(event->TaskIndex, x).c_str()));
        }
      }
      # endif // ifndef LIMIT_BUILD_SIZE
      success = true;
      break;
    }
  }
  return success;
}

#endif // USES_P033
