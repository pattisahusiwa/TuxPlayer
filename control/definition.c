#include "definition.h"
#include "rb_plugin.h"

#include "behaviour.h"
#include "method.h"
#include "tuxplayer.h"

//+++++++++++++++++++++++++++++++++
// Methods
//+++++++++++++++++++++++++++++++++
REALmethodDefinition ctlMethodDef[] = {
    // function, setterFunction, declaration, mFlags, attributeCount, attributes
    {(REALproc)tuxm_setFile, REALnoImplementation, "SetFile(fi as FolderItem)"},
    {(REALproc)tuxm_play, REALnoImplementation, "Play()"},
    {(REALproc)tuxm_pause, REALnoImplementation, "Pause()"},
    {(REALproc)tuxm_stop, REALnoImplementation, "Stop()"},
};

//+++++++++++++++++++++++++++++++++
// Behaviour
//+++++++++++++++++++++++++++++++++
REALcontrolBehaviour ctlBehaviourDef = {
    Constructor,           // constructorFunction
    NULL,                  // destructorFunction
    NULL,                  // redrawFunction
    NULL,                  // clickFunction
    NULL,                  // mouseDragFunction
    NULL,                  // mouseUpFunction
    NULL,                  // gainedFocusFunction
    NULL,                  // lostFocusFunction
    NULL,                  // keyDownFunction
    OnOpen,                // openFunction
    OnClose,               // closeFunction
    NULL,                  // backgroundIdleFunction
    OnDrawOffscreen,       // drawOffscreenFunction
    NULL,                  // setSpecialBackground
    NULL,                  // constantChanging
    NULL,                  // droppedNewInstance
    NULL,                  // mouseEnterFunction
    NULL,                  // mouseExitFunction
    NULL,                  // mouseMoveFunction
    NULL,                  // stateChangedFunction
    NULL,                  // actionEventFunction
    OnControlHandleGetter, // controlHandleGetter
    NULL,                  // mouseWheelFunction
    NULL,                  // enableMenuItemsFunction
    NULL,                  // menuItemActionFunction
    NULL,                  // controlAcceptFocus
    NULL,                  // keyUpFunction
    NULL,                  // redrawWithRectsFunction
    NULL,                  // unfilteredKeyDownFunction
    NULL,                  // scaleFactorChangedFunction
    NULL,                  // reserved2
    NULL                   // reserved3
    // end of struct
};

//+++++++++++++++++++++++++++++++++
// Plugin Control
//+++++++++++++++++++++++++++++++++
REALcontrol tuxPlayerDef = {
    kCurrentREALControlVersion,                          // version
    "TuxPlayer",                                         // name
    sizeof(ClassTuxPlayer),                              // dataSize
    REALcontrolAcceptFocus | REALdontEraseBackground,    // flags
    128,                                                 // toolbarPICT
    128,                                                 // toolbarDownPICT
    100,                                                 // defaultWidth
    100,                                                 // defaultHeight
    NULL,                                                // properties
    0,                                                   // propertyCount
    ctlMethodDef,                                        // methods
    sizeof(ctlMethodDef) / sizeof(REALmethodDefinition), // methodCount
    NULL,                                                // events
    0,                                                   // eventCount
    &ctlBehaviourDef,                                    // behaviour
    0,                                                   // forSystemUse
    NULL,                                                // eventInstances
    0,                                                   // eventInstanceCount
    NULL,                                                // interfaces
    NULL,                                                // attributes
    0,                                                   // attributeCount
    NULL,                                                // constants
    0,                                                   // constantCount
#if kCurrentREALControlVersion >= 11
    NULL, // sharedProperties;
    0,    // sharedPropertyCount;
    NULL, // sharedMethods;
    0,    // sharedMethodCount;
    NULL, // delegates;
    0,    // delegateCount;
    NULL, // enums;
    0,    // enumCount;
#endif
};

void registerControl(void)
{
    REALRegisterControl(&tuxPlayerDef);
}
