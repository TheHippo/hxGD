package;

import hxGD.Image;
import hxGD.Loader;
import hxGD.Color;
import hxGD.Polygon;
import hxGD.Graphics;

class Test1 {

	public function new() {
		
		var img:Image = Loader.createFromJpeg("test.jpg");
		
		trace("width: "+img.width+" height: "+img.height);
		
		//img.graphics.setBrush(brush);
		
		
		img.graphics.color = Color.ofRGB(0xFF0000);
		
	/*	var ca:Array<Color> = new Array<Color>();
		ca.push(new Color(255,0,0));
		ca.push(new Color(255,0,0));
		ca.push(new Color(0,255,0));
		ca.push(new Color(0,255,0));
		ca.push(new Color(0,0,255));
		ca.push(new Color(0,0,255));
		
		img.graphics.setStyle(ca); */
		img.graphics.thickness = 5;
		img.graphics.color = Color.ofRGBA(0xFF000055);
		
		img.graphics.imageLine(0,0,img.width,img.height,false);
		img.graphics.imageCircle(150,150,130);
		

		
		img.saveImage("test2.png",FileType.Png);
	}
	
	public static function main() {
		//for (i in 0...5000) {
			new Test1();	
		//	if (i % 10 == 0)
		//		neko.vm.Gc.run(true);
		//}
	}

}
