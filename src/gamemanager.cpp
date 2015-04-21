#include "oxygine-framework.h"
#include "resource.h"
#include <functional>
#include "gamename.h"
using namespace oxygine;

void gm_preinit() {

}

//başlangıçta entry_point.cpp tarafından çağrılacak
void gm_init()
{
    //kaynaklar ile ilgili tanımlamaların olduğu res.xml dosyasını içe aktar
    resource::load();

    GmGame game = new GameName;
    game->init();
    game->attachTo(getStage());
}

//her çizimde entry_point.cpp tarafından çağrılacak
void gm_update()
{

}

//her çizimde entry_point.cpp tarafından çağrılacak
void gm_destroy()
{
    //önceden yüklenmiş kaynakları bellekten boşalt
    resource::free();
}
