//
// Generated by dtk
// Translation Unit: d_kyeff.cpp
//

#include "f_op/f_op_kankyo.h"
#include "f_op/f_op_camera.h"
#include "d/d_com_inf_game.h"
#include "d/d_kankyo.h"
#include "d/d_kankyo_data.h"
#include "d/d_kankyo_wether.h"
#include "d/d_procname.h"
#include "d/d_stage.h"
#include "m_Do/m_Do_audio.h"
#include "dolphin/os/OS.h"

class dKyeff_c : public kankyo_class {
public:
    BOOL execute();
};

/* 80197FE4-80198008       .text dKyeff_Draw__FP8dKyeff_c */
BOOL dKyeff_Draw(dKyeff_c* i_this) {
    dKyw_wether_draw();
    return TRUE;
}

/* 80198008-8019803C       .text get_parcent__Ffff */
static f32 get_parcent(f32 param_0, f32 param_1, f32 param_2) {
    f32 temp_f1;
    f32 temp_f2;
    f32 temp_f4 = param_0 - param_1;

    if (0.0f != temp_f4) {
        temp_f1 = 1.0f - (param_0 - param_2) / temp_f4;
        if (!(temp_f1 >= 1.0f)) {
            return temp_f1;
        }
    }
    return 1.0f;
}

/* 8019803C-8019808C       .text s16_data_ratio_set__Fssf */
static s16 s16_data_ratio_set(s16 param_0, s16 param_1, f32 param_2) {
    return param_0 + (s16)(param_2 * (param_1 - param_0));
}


/* 8019808C-8019847C       .text menu_vrbox_set__Fv */
void menu_vrbox_set() {
    f32 blendPalAB, curTime;
    stage_vrbox_info_class* vrbox;
    stage_vrbox_info_class* vrbox0;
    stage_vrbox_info_class* vrbox1;

    camera_class * pCamera = dComIfGp_getCamera(0);

    pCamera->mLookat.mEye.x = 9377.0f;
    pCamera->mLookat.mEye.y = 0.0f;
    pCamera->mLookat.mEye.z = 7644.0f;
    pCamera->mLookat.mCenter.x = 4300.0f;
    pCamera->mLookat.mCenter.y = 4200.0f;
    pCamera->mLookat.mCenter.z = 1000.0f;

    g_env_light.mWind.mWindPower = 0.7f;
    curTime = g_env_light.mCurTime;

    g_env_light.mCurTime += 0.03f;
    if ((u32)g_env_light.mCurTime >= 360.0f)
        g_env_light.mCurTime = 0.0f;

    mDoAud_setHour(curTime / 15.0f);
    mDoAud_setMinute(((s32)(curTime * 1000000.0f) % 15000000) / 1000000.0f);

    g_env_light.mpSchejule = dKyd_schejule_menu_getp();

    u8 palIdx0, palIdx1;
    for (s32 i = 0; i < 11; i++) {
        if (curTime >= g_env_light.mpSchejule[i].mTimeEnd && curTime <= g_env_light.mpSchejule[i].mTimeBegin) {
            palIdx0 = g_env_light.mpSchejule[i].mPalIdx0;
            palIdx1 = g_env_light.mpSchejule[i].mPalIdx1;
            blendPalAB = get_parcent(g_env_light.mpSchejule[i].mTimeBegin, g_env_light.mpSchejule[i].mTimeEnd, curTime);
        }
    }

    vrbox = dKyd_dmvrbox_getp();
    g_env_light.mpVrboxInfo = vrbox;

    vrbox0 = &vrbox[palIdx0];
    vrbox1 = &vrbox[palIdx1];
    g_env_light.mVrSkyColor.r = s16_data_ratio_set(vrbox0->mSkyColor.r, vrbox1->mSkyColor.r, blendPalAB);
    g_env_light.mVrSkyColor.g = s16_data_ratio_set(vrbox0->mSkyColor.g, vrbox1->mSkyColor.g, blendPalAB);
    g_env_light.mVrSkyColor.b = s16_data_ratio_set(vrbox0->mSkyColor.b, vrbox1->mSkyColor.b, blendPalAB);
    g_env_light.mVrkumoColor.r = s16_data_ratio_set(vrbox0->mKumoColor.r, vrbox1->mKumoColor.r, blendPalAB);
    g_env_light.mVrkumoColor.g = s16_data_ratio_set(vrbox0->mKumoColor.g, vrbox1->mKumoColor.g, blendPalAB);
    g_env_light.mVrkumoColor.b = s16_data_ratio_set(vrbox0->mKumoColor.b, vrbox1->mKumoColor.b, blendPalAB);
    g_env_light.mVrkumoCenterColor.r = s16_data_ratio_set(vrbox0->mKumoCenterColor.r, vrbox1->mKumoCenterColor.r, blendPalAB);
    g_env_light.mVrkumoCenterColor.g = s16_data_ratio_set(vrbox0->mKumoCenterColor.g, vrbox1->mKumoCenterColor.g, blendPalAB);
    g_env_light.mVrkumoCenterColor.b = s16_data_ratio_set(vrbox0->mKumoCenterColor.b, vrbox1->mKumoCenterColor.b, blendPalAB);
    g_env_light.mVrKasumiMaeColor.r = (u8)(g_env_light.mVrkumoColor.r * 0.9f);
    g_env_light.mVrKasumiMaeColor.g = (u8)(g_env_light.mVrkumoColor.g * 0.9f);
    g_env_light.mVrKasumiMaeColor.b = (u8)(g_env_light.mVrkumoColor.b * 0.9f);
    g_env_light.mVrUsoUmiColor.r = (u8)(g_env_light.mVrkumoColor.r * 0.9f);
    g_env_light.mVrUsoUmiColor.g = (u8)(g_env_light.mVrkumoColor.g * 0.9f);
    g_env_light.mVrUsoUmiColor.b = (u8)(g_env_light.mVrkumoColor.b * 0.9f);
    g_env_light.mVrkumoColor.a = 0xFF;
}

/* 8019847C-801984CC       .text execute__8dKyeff_cFv */
BOOL dKyeff_c::execute() {
    if (strcmp(dComIfGp_getStartStageName(), "Name") == 0) {
        menu_vrbox_set();
    } else {
        dKyw_wether_move();
    }

    dKyw_wether_move_draw();
    return TRUE;
}

/* 801984CC-801984EC       .text dKyeff_Execute__FP8dKyeff_c */
BOOL dKyeff_Execute(dKyeff_c* i_this) {
    return i_this->execute();
}

/* 801984EC-801984F4       .text dKyeff_IsDelete__FP8dKyeff_c */
BOOL dKyeff_IsDelete(dKyeff_c* i_this) {
    return TRUE;
}

/* 801984F4-80198518       .text dKyeff_Delete__FP8dKyeff_c */
BOOL dKyeff_Delete(dKyeff_c* i_this) {
    dKyw_wether_delete();
    return TRUE;
}

/* 80198518-80198758       .text dKyeff_Create__FP12kankyo_class */
s32 dKyeff_Create(kankyo_class* i_ky) {
    dKyw_wether_init();

    if (strcmp(dComIfGp_getStartStageName(), "Name") == 0) {
        OSCalendarTime cal;
        OSTime curTime = OSGetTime();
        OSTicksToCalendarTime(curTime, &cal);

        g_env_light.mWind.mWindVec.set(1.0f, 0.0f, 0.0f);
        g_env_light.mWind.mWindPower = 0.7f;

        g_env_light.mCurTime = 15.0f * cal.hours;
    } else if (dKy_checkEventNightStop()) {
        u32 stType = dStage_stagInfo_GetSTType(dComIfGp_getStage().getStagInfo());
        if (stType == dStageType_OUTDOORS_e || stType == dStageType_SEA_e) {
            dKyw_rain_set(250);
            g_env_light.mThunderEff.mMode = 1;
        } else if (stType == dStageType_MISC_e) {
            if (strcmp(dComIfGp_getStartStageName(), "Ocrogh") == 0 || strcmp(dComIfGp_getStartStageName(), "Omori") == 0 ||
                strcmp(dComIfGp_getStartStageName(), "Orichh") == 0 || strcmp(dComIfGp_getStartStageName(), "Atorizk") == 0 ||
                strcmp(dComIfGp_getStartStageName(), "LinkRM") == 0 || strcmp(dComIfGp_getStartStageName(), "Ojhous2") == 0 ||
                strcmp(dComIfGp_getStartStageName(), "Onobuta") == 0 || strcmp(dComIfGp_getStartStageName(), "Omasao") == 0 ||
                strcmp(dComIfGp_getStartStageName(), "Obombh") == 0 || strcmp(dComIfGp_getStartStageName(), "Opub") == 0) {
                dKyw_rain_set(250);
                g_env_light.mThunderEff.mMode = 10;
            }
        }
    }

    return cPhs_COMPLEATE_e;
}

kankyo_method_class l_dKyeff_Method = {
    (process_method_func)dKyeff_Create,
    (process_method_func)dKyeff_Delete,
    (process_method_func)dKyeff_Execute,
    (process_method_func)dKyeff_IsDelete,
    (process_method_func)dKyeff_Draw,
};

kankyo_process_profile_definition g_profile_KYEFF = {
    fpcLy_CURRENT_e,
    12,
    fpcPi_CURRENT_e,
    PROC_KYEFF,
    &g_fpcLf_Method.mBase,
    sizeof(dKyeff_c),
    0,
    0,
    &g_fopKy_Method,
    0x005,
    &l_dKyeff_Method,
};
