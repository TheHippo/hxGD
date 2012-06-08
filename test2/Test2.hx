import hxGD.Loader;
import hxGD.Image.FileType;

class Test2 {
	
	public static function main() {
		var img = Loader.createFromPng("test2.png");
		img.resize(Math.round(img.width / 2), Math.round(img.height / 2), true);
		img.saveImage("test2_resized.png", Png);
		img = Loader.createFromGif("test2.gif");
		img.resize(Math.round(img.width * 2), Math.round(img.height * 2), true);
		img.saveImage("test2_resized.gif", Gif);
		var img = Loader.createFromJpeg("test2.jpg");
		img.resize(Math.round(img.width / 2), Math.round(img.height / 2), true);
		img.saveImage("test2_resized.jpg", Jpeg(90));
	}
	
}
