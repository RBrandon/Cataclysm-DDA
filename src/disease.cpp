#include "rng.h"
#include "game.h"
#include "monster.h"
#include "bodypart.h"
#include "disease.h"
#include "weather.h"
#include "translations.h"
#include "martialarts.h"
#include "monstergenerator.h"
#include "messages.h"
#include <stdlib.h>
#include <sstream>
#include <algorithm>

// Used only internally for fast lookups.
enum dis_type_enum {
 DI_NULL,
// Martial arts-related buffs
 DI_MA_BUFF
};

std::map<std::string, dis_type_enum> disease_type_lookup;

void game::init_diseases() {
    // Initialize the disease lookup table.

    disease_type_lookup["null"] = DI_NULL;
    disease_type_lookup["ma_buff"] = DI_MA_BUFF;
}

bool dis_msg(dis_type type_string) {
    dis_type_enum type = disease_type_lookup[type_string];
    switch (type) {
    default:
        return false;
        break;
    }

    return true;
}

void dis_end_msg(player &p, disease &dis)
{
    switch (disease_type_lookup[dis.type]) {
    default:
        break;
    }
}

void dis_remove_memorial(dis_type type_string) {

  dis_type_enum type = disease_type_lookup[type_string];

  switch(type) {

    default:
        break;
  }

}

void dis_effect(player &p, disease &dis)
{
    dis_type_enum disType = disease_type_lookup[dis.type];

    switch(disType) {
        case DI_MA_BUFF:
            if (ma_buffs.find(dis.buff_id) != ma_buffs.end()) {
              ma_buff b = ma_buffs[dis.buff_id];
              if (b.is_valid_player(p)) {
                b.apply_player(p);
              }
              else {
                p.rem_disease(dis.type);
              }
            }
            break;
        default: // Other diseases don't have any effects. Suppress warning.
            break;
    }
}

int disease_speed_boost(disease dis)
{
    dis_type_enum type = disease_type_lookup[dis.type];
    switch (type) {
        default:            break;
    }
    return 0;
}

std::string dis_name(disease& dis)
{
    // Maximum length of returned string is 26 characters
    dis_type_enum type = disease_type_lookup[dis.type];
    switch (type) {
    case DI_NULL: return "";

    case DI_MA_BUFF:
        if (ma_buffs.find(dis.buff_id) != ma_buffs.end()) {
            std::stringstream buf;
            if (ma_buffs[dis.buff_id].max_stacks > 1) {
                buf << ma_buffs[dis.buff_id].name << " (" << dis.intensity << ")";
                return buf.str();
            } else {
                buf << ma_buffs[dis.buff_id].name.c_str();
                return buf.str();
            }
        } else
            return "Invalid martial arts buff";

    default: break;
    }
    return "";
}

std::string dis_description(disease& dis)
{
    std::stringstream stream;
    dis_type_enum type = disease_type_lookup[dis.type];
    switch (type) {

    case DI_NULL:
        return _("None");

    case DI_MA_BUFF:
        if (ma_buffs.find(dis.buff_id) != ma_buffs.end())
          return ma_buffs[dis.buff_id].description.c_str();
        else
          return "This is probably a bug.";
    default: break;
    }
    return "Who knows?  This is probably a bug. (disease.cpp:dis_description)";
}
