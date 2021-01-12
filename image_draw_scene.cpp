#include "image_draw_scene.hpp"


// ==============================================
// private functions [START]
// ==============================================


// ==============================================
// private functions [END]
// ==============================================

ImageDrawScene::ImageDrawScene(QObject* parent)
    : QGraphicsScene(parent)
{}

ImageDrawScene::~ImageDrawScene()
{}

void ImageDrawScene::switch_visual_objects(VisualObjectType type, bool is_show)
{}

QImage ImageDrawScene::get_dib_image() const
{
    return scene_image.source_dib_qimage;
}

bool ImageDrawScene::set_dib_image(const QImage& image, bool is_raw)
{
    if (image.isNull())
    {
        return false;
    }

    // QImage
    scene_image.source_dib_qimage = image.copy();
    if (is_raw)
    {
        scene_image.raw_dib_qimage = image.copy();
    }

    // QPixmap
    // ディスプレイに表示するQImageはARGB32(0xffRRGGBB)フォーマットで統一される
    scene_image.off_screen_ddb_qpixmap = QPixmap::fromImage(scene_image.source_dib_qimage);

    // QGraphicsPixmapの生成or更新
    if (auto& items_on_scene = this->items(); items_on_scene.contains<QPixmap*>(&(scene_image.off_screen_ddb_qpixmap)))
    {
        scene_image.item_qpixmap = make_shared<QGraphicsPixmapItem>(scene_image.off_screen_ddb_qpixmap);
        addItem(scene_image.item_qpixmap.get()); // TODO: 生ポインタを渡すことになるけど、データ構造これで大丈夫？
    }
    else
    {
        scene_image.item_qpixmap.setPixmap(scene_image.off_screen_ddb_qpixmap); // 中身だけ書き換える
    }

    // QPixmapの画像サイズをSceneサイズに登録
    setSceneRect(scene_image.off_screen_ddb_qpixmap.rect());

    // ImageWindow(親Widget)のステータスバーにSceneサイズを表示させる
    // ここで, QtのSignalを発行して、ImageWindow側でステータスバー表示を行う. 2021/01/11 shinichi.

}

