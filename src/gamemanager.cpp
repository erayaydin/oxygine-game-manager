#include "oxygine-framework.h"
#include "resource.h"
#include <functional>
using namespace oxygine;

void gm_preinit() {

}

//başlangıçta entry_point.cpp tarafından çağrılacak
void gm_init()
{
    //kaynaklar ile ilgili tanımlamaların olduğu res.xml dosyasını içe aktar
    resource::load();

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
