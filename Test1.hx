import hxGD.Image;
class Test1 {
	public static function main() {
		hxGD.Image.defaultBackgroundColor = new hxGD.Color(255,255,255);
		var i = new hxGD.Image(100, 100, new hxGD.Color(0,0,0), true);
		i.graphics.line(0,0,100,100);
		if (neko.Web.isModNeko) {
			neko.Web.setHeader("Content-Type","image/png");
			neko.Lib.print(i.getImageData(FileType.Png));
		}
		else
			i.saveImage("test.jpg",FileType.Jpeg(90));
	}
}
