//
// Generated by dtk
// Translation Unit: d_a_tag_island.cpp
//

#include "d/actor/d_a_tag_island.h"
#include "d/actor/d_a_obj_ikada.h"
#include "d/actor/d_a_player_main.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"

static uint l_msgId;
static msg_class* l_msg;

enum {
    ACT_HUNT,
    ACT_ARRIVAL,
    ACT_WAIT,
    ACT_READY,
    ACT_EVENT,
    ACT_TACT,
};

enum {
    EVENT_WAIT,
    EVENT_SPEAK,
    EVENT_TACT_BF,
    EVENT_TACT_MD,
    EVENT_TACT_AF,
};

/* 00000078-00000084       .text getEventNo__14daTag_Island_cFv */
u8 daTag_Island_c::getEventNo() {
    return (fopAcM_GetParam(this) >> 24) & 0xFF;
}

/* 00000084-00000090       .text getSwbit__14daTag_Island_cFv */
u8 daTag_Island_c::getSwbit() {
    return (fopAcM_GetParam(this) >> 8) & 0xFF;
}

/* 00000090-0000009C       .text getType__14daTag_Island_cFv */
u8 daTag_Island_c::getType() {
    return (fopAcM_GetParam(this) >> 0) & 0xFF;
}

/* 0000009C-000001D8       .text checkArea__14daTag_Island_cFv */
BOOL daTag_Island_c::checkArea() {
    fopAc_ac_c* player = dComIfGp_getLinkPlayer();
    cXyz delta = player->current.pos - current.pos;
    if (delta.y < 0.0f)
        delta.y = -delta.y;
    f32 distXZ = delta.absXZ();
    if (distXZ < scale.x * 10000.0f && delta.y <= scale.y * 10000.0f)
        return TRUE;
    return FALSE;
}

/* 000001D8-00000354       .text makeEvId__14daTag_Island_cFv */
void daTag_Island_c::makeEvId() {
    mEventId = dComIfGp_evmng_getEventIdx(NULL, getEventNo());

    if (!dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
        s16 idx;

        switch (getType()) {
        case 1: idx = dComIfGp_evmng_getEventIdx("ARRIVAL_DRG2"); break;
        case 2: idx = dComIfGp_evmng_getEventIdx("ARRIVAL_GND2"); break;
        case 3: idx = dComIfGp_evmng_getEventIdx("ARRIVAL_WND2"); break;
        case 4: idx = dComIfGp_evmng_getEventIdx("ARRIVAL_TWN2"); break;
        case 5: idx = dComIfGp_evmng_getEventIdx("ARRIVAL_FST2"); break;
        case 6: idx = dComIfGp_evmng_getEventIdx("ARRIVAL_BRK2"); break;
        case 7: idx = dComIfGp_evmng_getEventIdx("PUROLO_RETURN2"); break;
        }

        if (idx != -1)
            mEventId = idx;
    }
}

/* 00000354-000003D4       .text getArrivalFlag__14daTag_Island_cFv */
u16 daTag_Island_c::getArrivalFlag() {
    switch (getType()) {
    case 1: return 0x0902;
    case 2: return 0x0A20;
    case 3: return 0x0A02;
    case 4: return 0x1F04;
    case 5: return 0x2E04;
    case 6: return 0x2E02;
    case 7: return 0x3E10;
    default: return 0;
    }
}

/* 000003D4-0000045C       .text otherCheck__14daTag_Island_cFv */
BOOL daTag_Island_c::otherCheck() {
    switch (getType()) {
    case 5:
        if (!dComIfGs_isEventBit(0x1608))
            return FALSE;
        break;
    case 6:
        if (!dComIfGs_isEventBit(0x1604))
            return FALSE;
        break;
    }

    return TRUE;
}

/* 0000045C-00000514       .text arrivalTerms__14daTag_Island_cFv */
BOOL daTag_Island_c::arrivalTerms() {
    if (dComIfGs_isEventBit(getArrivalFlag()))
        return FALSE;

    switch (getType()) {
    case 4:
        if (!dKy_checkEventNightStop())
            return FALSE;
        break;
    case 7:
        if (!dKy_checkEventNightStop())
            return FALSE;
        if (!dComIfGs_checkGetItem(dItem_BOMB_BAG_e))
            return FALSE;
        break;
    }

    return TRUE;
}

/* 00000514-00000550       .text demoInitProc__14daTag_Island_cFv */
void daTag_Island_c::demoInitProc() {
    m290 = 0;
    dComIfGs_onEventBit(getArrivalFlag());
}

/* 00000550-00000558       .text next_msgStatus__14daTag_Island_cFPUl */
int daTag_Island_c::next_msgStatus(unsigned long*) {
    return fopMsgStts_MSG_ENDS_e;
}

/* 00000558-00000560       .text getMsg__14daTag_Island_cFv */
u32 daTag_Island_c::getMsg() {
    return m2AC;
}

/* 00000560-0000056C       .text talkInit__14daTag_Island_cFv */
void daTag_Island_c::talkInit() {
    mTalkState = 0;
}

/* 0000056C-000006AC       .text talk__14daTag_Island_cFv */
u16 daTag_Island_c::talk() {
    /* Nonmatching */
    u16 ret = 0xFF;
    switch (mTalkState) {
    case 0:
        l_msgId = fpcM_ERROR_PROCESS_ID_e;
        mMsg = getMsg();
        mTalkState = 1;
        break;
    case 1:
        l_msg = fopMsgM_SearchByID(l_msgId);
        if (l_msg != NULL)
            mTalkState = 2;
        break;
    case 2:
        if (l_msgId == fpcM_ERROR_PROCESS_ID_e)
            l_msgId = fopMsgM_messageSet(mMsg, this);

        ret = l_msg->mStatus;
        if (ret == fopMsgStts_MSG_DISPLAYED_e) {
            l_msg->mStatus = next_msgStatus(&mMsg);
            if (l_msg->mStatus == fopMsgStts_MSG_CONTINUES_e) {
                fopMsgM_messageSet(mMsg);
            }
        } else if (ret == fopMsgStts_BOX_CLOSED_e) {
            l_msg->mStatus = fopMsgStts_MSG_DESTROYED_e;
            mTalkState = -1;
        }
        break;
    }

    return ret;
}

/* 000006AC-00000778       .text demoInitTact_Bf__14daTag_Island_cFv */
void daTag_Island_c::demoInitTact_Bf() {
    talkInit();

    s32* a_intP = (s32*)dComIfGp_evmng_getMyIntegerP(mStaffId, "prm0");
    JUT_ASSERT(0x167, a_intP);

    if (a_intP != NULL) {
        dComIfGp_setMelodyNum(*a_intP);
        if (*a_intP == 6) {
            m2AC = 0x05B4;
        } else {
            m2AC = 0x05B3;
        }
    }
}

/* 00000778-000007C8       .text demoProcTact_Bf__14daTag_Island_cFv */
BOOL daTag_Island_c::demoProcTact_Bf() {
    if (talk() == fopMsgStts_UNK15_e)
        dComIfGp_evmng_cutEnd(mStaffId);
    return TRUE;
}

/* 000007C8-00000854       .text demoInitTact_Af__14daTag_Island_cFv */
void daTag_Island_c::demoInitTact_Af() {
    daPy_lk_c* player = daPy_getPlayerLinkActorClass();
    l_msg->mStatus = fopMsgStts_MSG_ENDS_e;
    fopMsgM_messageSendOn();
    if (player->getTactTimerCancel() > 0)
        setFlag(0x04);
    else
        clrFlag(0x04);
}

/* 00000854-00000A00       .text demoProcTact_Af__14daTag_Island_cFv */
BOOL daTag_Island_c::demoProcTact_Af() {
    /* Nonmatching */
    u16 rt = talk();
    if (rt == fopMsgStts_BOX_CLOSED_e || rt == 0xFE) {
        if (chkFlag(0x01)) {
            clrFlag(0x01);
            if (chkFlag(0x04)) {
                if (m2A0 == 1) {
                    mEventId = dComIfGp_evmng_getEventIdx("TACT_TEARCH4");
                } else {
                    mEventId = dComIfGp_evmng_getEventIdx("TACT_TEARCH1");
                }
            } else {
                if (m2A0 == 0) {
                    m2A0 = 1;
                    mEventId = dComIfGp_evmng_getEventIdx("TACT_TEARCH2");
                } else {
                    mEventId = dComIfGp_evmng_getEventIdx("TACT_TEARCH3");
                }
            }
            setFlag(0x02);
            fopAcM_orderChangeEventId(this, daPy_getPlayerLinkActorClass(), mEventId, 0, 0xFFFF);
        } else {
            JUT_ASSERT(0x1b3, 0);
            dComIfGp_evmng_cutEnd(mStaffId);
        }
    }

    return TRUE;
}

/* 00000A00-00000AC4       .text demoInitSpeak__14daTag_Island_cFv */
void daTag_Island_c::demoInitSpeak() {
    /* Nonmatching */
    talkInit();
    s32* a_intP = (s32*)dComIfGp_evmng_getMyIntegerP(mStaffId, "MsgNo");
    JUT_ASSERT(0x1C2, a_intP);

    m2AC = *a_intP;
    if (m2AC == 0x0638 && m2A0 != 0)
        m2AC = 0x063A;
}

/* 00000AC4-00000B1C       .text demoProcSpeak__14daTag_Island_cFv */
BOOL daTag_Island_c::demoProcSpeak() {
    u16 rt = talk();
    if (rt == fopMsgStts_BOX_CLOSED_e || rt == 0xFE)
        dComIfGp_evmng_cutEnd(mStaffId);
    return FALSE;
}

/* 00000B1C-00000B84       .text demoInitWait__14daTag_Island_cFv */
void daTag_Island_c::demoInitWait() {
    /* Nonmatching */
    s32* a_intP = (s32*)dComIfGp_evmng_getMyIntegerP(mStaffId, "Timer");
    if (a_intP != NULL)
        mTimer = *a_intP;
    else
        mTimer = 0;
}

/* 00000B84-00000BD4       .text demoProcWait__14daTag_Island_cFv */
BOOL daTag_Island_c::demoProcWait() {
    if (mTimer > 0)
        mTimer--;
    else
        dComIfGp_evmng_cutEnd(mStaffId);
    return FALSE;
}

/* 00000BD4-00000BE4       .text demoInitCom__14daTag_Island_cFv */
void daTag_Island_c::demoInitCom() {
    setFlag(0x01);
}

/* 00000BE4-00000BE8       .text demoProcCom__14daTag_Island_cFv */
BOOL daTag_Island_c::demoProcCom() {
}

/* 00000BE8-00000CFC       .text demoProcCom_ikada__14daTag_Island_cFv */
BOOL daTag_Island_c::demoProcCom_ikada() {
    /* Nonmatching */
    daObj_Ikada_c* ikada = (daObj_Ikada_c*)fopAcM_searchFromName("ikada_h", 0, 0);
    if (ikada != NULL) {
        ikada->mCurPathP0 = ikada->mInitPos;
        ikada->current.pos = ikada->mCurPathP0;
        ikada->mCurPathPoint = 0;
        ikada->m02CC = ikada->mpPath->mpPnt[ikada->mCurPathPoint].mPos;
        ikada->mCurPathP1 = ikada->mpPath->mpPnt[ikada->mCurPathPoint + 1].mPos;
        ikada->mPathPosTarget = ikada->mpPath->mpPnt[ikada->mCurPathPoint].mPos;
    }
}

/* 00000CFC-00000D44       .text getNowEventAction__14daTag_Island_cFv */
int daTag_Island_c::getNowEventAction() {
    static const char *action_table[] = {
        "WAIT",
        "SPEAK",
        "TACT_BF",
        "TACT_MD",
        "TACT_AF",
    };

    return dComIfGp_evmng_getMyActIdx(mStaffId, (char**)action_table, ARRAY_SIZE(action_table), FALSE, 1);
}

/* 00000D44-00000EDC       .text demoProc__14daTag_Island_cFv */
BOOL daTag_Island_c::demoProc() {
    BOOL ret = FALSE;

    if (chkFlag(0x02)) {
        mStaffId = dComIfGp_evmng_getMyStaffId("TagIsl");
        clrFlag(0x02);
        dComIfGp_event_setTalkPartner(dComIfGp_getShipActor());
    }

    int action = getNowEventAction();
    if (dComIfGp_evmng_getIsAddvance(mStaffId)) {
        demoInitCom();
        switch (action) {
        case EVENT_SPEAK: demoInitSpeak(); break;
        case EVENT_WAIT: demoInitWait(); break;
        case EVENT_TACT_BF: demoInitTact_Bf(); break;
        case EVENT_TACT_AF: demoInitTact_Af(); break;
        }
    }

    switch (action) {
    case EVENT_SPEAK: ret = demoProcSpeak(); break;
    case EVENT_WAIT: demoProcWait(); break;
    case EVENT_TACT_BF: ret = demoProcTact_Bf(); break;
    case EVENT_TACT_AF: ret = demoProcTact_Af(); break;
    default: dComIfGp_evmng_cutEnd(mStaffId); break;
    }

    demoProcCom();
    return ret;
}

/* 00000EDC-00000F4C       .text actionTact__14daTag_Island_cFv */
BOOL daTag_Island_c::actionTact() {
    if (dComIfGp_evmng_endCheck(mEventId)) {
        setActio(ACT_HUNT);
        dComIfGp_event_reset();
    } else {
        demoProc();
    }
    return TRUE;
}

/* 00000F4C-00001034       .text actionEvent__14daTag_Island_cFv */
BOOL daTag_Island_c::actionEvent() {
    /* Nonmatching */
    if (dComIfGp_evmng_endCheck(mEventId)) {
        if (getType() == 1) {
            setFlag(0x02);
            setActio(ACT_TACT);
            mEventId = dComIfGp_evmng_getEventIdx("TACT_TEARCH0");
            fopAcM_orderChangeEventId(this, daPy_getPlayerLinkActorClass(), mEventId, 0, 0xFFFF);
            m2A0 = 0;
        } else {
            setActio(ACT_HUNT);
            dComIfGp_event_reset();
        }
    } else {
        demoProcCom_ikada();
    }
    return TRUE;
}

/* 00001034-00001130       .text actionReady__14daTag_Island_cFv */
BOOL daTag_Island_c::actionReady() {
    s32 swbit = getSwbit();
    if (eventInfo.checkCommandDemoAccrpt()) {
        demoInitProc();
        dComIfGp_event_setTalkPartner(dComIfGp_getShipActor());
        setActio(ACT_EVENT);
        actionEvent();
        if (swbit != 0xFF)
            dComIfGs_onSwitch(swbit, current.roomNo);
    } else if (swbit != 0xFF && dComIfGs_isSwitch(swbit, current.roomNo)) {
        setActio(ACT_HUNT);
    } else {
        makeEvId();
        fopAcM_orderOtherEventId(this, mEventId);
    }
    return TRUE;
}

/* 00001130-000011E4       .text actionHunt__14daTag_Island_cFv */
BOOL daTag_Island_c::actionHunt() {
    s32 swbit = getSwbit();
    if (swbit != 0xFF && dComIfGs_isSwitch(swbit, current.roomNo)) {
        setActio(ACT_HUNT);
    } else {
        if (otherCheck() && checkArea()) {
            makeEvId();
            setActio(ACT_READY);
            fopAcM_orderOtherEventId(this, mEventId);
        }
    }
    return TRUE;
}

/* 000011E4-00001238       .text actionArrival__14daTag_Island_cFv */
BOOL daTag_Island_c::actionArrival() {
    if (arrivalTerms()) {
        setActio(ACT_WAIT);
        actionHunt();
    } else {
        setActio(ACT_HUNT);
    }
    return TRUE;
}

/* 00001238-00001240       .text actionWait__14daTag_Island_cFv */
BOOL daTag_Island_c::actionWait() {
    return TRUE;
}

s32 daTag_Island_c::create() {
    fopAcM_SetupActor(this, daTag_Island_c);
    s32 swbit = getSwbit();
    makeEvId();
    eventInfo.setEventId(mEventId);
    eventInfo.mMapToolId = getEventNo();

    if (mEventId != -1 && swbit != 0xFF && !dComIfGs_isSwitch(swbit, current.roomNo)) {
        setActio(ACT_ARRIVAL);
    } else {
        setActio(ACT_HUNT);
    }
    shape_angle.x = shape_angle.z = 0;
    current.angle.x = current.angle.z = 0;
    return cPhs_COMPLEATE_e;
}

BOOL daTag_Island_c::draw() {
    return TRUE;
}

BOOL daTag_Island_c::execute() {
    /* Nonmatching */
    switch (mAction) {
    case ACT_ARRIVAL:
        actionArrival();
        break;
    case ACT_HUNT:
    default:
        actionHunt();
        break;
    case ACT_READY:
        actionReady();
        break;
    case ACT_EVENT:
        actionEvent();
        break;
    case ACT_TACT:
        actionTact();
        break;
    case ACT_WAIT:
        actionWait();
        break;
    }

    return TRUE;
}

/* 00001240-00001248       .text daTag_Island_Draw__FP14daTag_Island_c */
static BOOL daTag_Island_Draw(daTag_Island_c* i_this) {
    return i_this->draw();
}

/* 00001248-000012C4       .text daTag_Island_Execute__FP14daTag_Island_c */
static BOOL daTag_Island_Execute(daTag_Island_c* i_this) {
    return i_this->execute();
}

/* 000012C4-000012CC       .text daTag_Island_IsDelete__FP14daTag_Island_c */
static BOOL daTag_Island_IsDelete(daTag_Island_c* i_this) {
    return TRUE;
}

/* 000012CC-000012FC       .text daTag_Island_Delete__FP14daTag_Island_c */
static BOOL daTag_Island_Delete(daTag_Island_c* i_this) {
    i_this->~daTag_Island_c();
    return TRUE;
}

/* 000012FC-000013D8       .text daTag_Island_Create__FP10fopAc_ac_c */
static s32 daTag_Island_Create(fopAc_ac_c* i_ac) {
    return ((daTag_Island_c*)i_ac)->create();
}

static actor_method_class l_daTag_Island_Method = {
    (process_method_func)daTag_Island_Create,
    (process_method_func)daTag_Island_Delete,
    (process_method_func)daTag_Island_Execute,
    (process_method_func)daTag_Island_IsDelete,
    (process_method_func)daTag_Island_Draw,
};

actor_process_profile_definition g_profile_TAG_ISLAND = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_TAG_ISLAND,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daTag_Island_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x0123,
    /* Actor SubMtd */ &l_daTag_Island_Method,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_6_e,
};
