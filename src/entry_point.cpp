#include "core/oxygine.h"
#include "Stage.h"
#include "DebugActor.h"

#include "gamemanager.h"


using namespace oxygine;

/*
 * Main looping function
 * Loading in every frame...
 */
int mainloop()
{
    gm_update();
    // sahneyi ve bütün elemanları güncelle
    getStage()->update();

    if (core::beginRendering())
    {
        Color clearColor(32, 32, 32, 255);
        Rect viewport(Point(0, 0), core::getDisplaySize());
        //tüm elemanları çiz. Her elemanın Actor::render fonksiyonu çağrılacaktır
        getStage()->render(clearColor, viewport);

        core::swapDisplayBuffers();
    }

    // eğer `done` true ise kullanıcı uygulamadan çıkmak istiyor
    bool done = core::update();

    return done ? 1 : 0;
}

/*
 * Uygulamanın başlatıldığı fonksiyon
 */
void run()
{
    ObjectBase::__startTracingLeaks();

    // Oxygine'in gereksinimleri başlatılıyor
    core::init_desc desc;

#if OXYGINE_SDL || OXYGINE_EMSCRIPTEN
    //SDL'de belirtmek istediğimiz pencere büyüklüğü
    desc.w = 960;
    desc.h = 640;
    //marmalade ayarları emualator'un menusundan ayarlanabilir
#endif


    gm_preinit();
    core::init(&desc);


    //Sahneyi oluştur. Sahne, bütün nesneleri barındaracak ana kök olacaktır.
    Stage::instance = new Stage(true);
    Point size = core::getDisplaySize();
    getStage()->setSize(size);

    //DebugActor, yardımcı bir element. FPS, bellek kullanımı gibi yararlı şeyleri gösterecek
    DebugActor::show();

    //Uygulamayı başlat
    gm_init();

#ifdef EMSCRIPTEN
    return;
#endif


    // ana oyun döngüsü
    while (1)
    {
        int done = mainloop();
        if (done)
            break;
    }
    //uygulama bitti, çıkış işlemleri başlıyor...

    //Oluşturulmuş objeleri loga dökelim
    //tüm oluşturulmuş nesneler ve kaynaktan silinmemiş olanlar gözükecektir
    ObjectBase::dumpCreatedObjects();

    //artık her şeyi temizleyebiliriz. Bunun için ObjectBase::dumpObjects() fonksiyonunu çalıştıracağız
    //kullandığımız kaynakları ve oluşturduğumuz bütün nesneleri silmeliyiz.
    //tüm nesne/çizim birer objedir ve bunları teker teker kaynaktan silmenize gerek yok.
    //fakat şimdilik bunu teker teker yapacağız

    // uygulamanın bitiş işlemlerini çağır
    gm_destroy();


    //renderer.cleanup();

    /**tüm kullanılan modülleri ve sahneyi kaldır*/
    core::release();

    //artık log listemiz boş olmalı
    //her şeyi sildik ve boş yere hiçbir hafıza kullanımı yapmadık
    ObjectBase::dumpCreatedObjects();

    ObjectBase::__stopTracingLeaks();
    //bitiş
}

#ifdef __S3E__
int main(int argc, char* argv[])
{
    run();
    return 0;
}
#endif


#ifdef OXYGINE_SDL

#include "SDL_main.h"
extern "C"
{
    int main(int argc, char* argv[])
    {
        run();
        return 0;
    }
};
#endif

#ifdef EMSCRIPTEN
#include <emscripten.h>

void one() { mainloop(); }

int main(int argc, char* argv[])
{
    run();
    emscripten_set_main_loop(one, 0, 0);
    return 0;
}
#endif
