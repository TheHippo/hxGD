package hxGD;

class Color {

	public var gd(gdColor,null):Int;
	public var red:Int;
	public var green:Int;
	public var blue:Int;
	public var alpha:Int;
	
	public function new(red:Int,green:Int,blue:Int,?alpha:Int=255) {
		this.red = red;
		this.green = green;
		this.blue = blue;
		this.alpha = alpha;
	//	trace(this);
	}
	
	public static inline function ofRGB(color:Int):Color {
		//0xRRGGBB
		return new Color(((color & 0xFF0000) >> 16),((color & 0x00FF00) >> 8),(color & 0x0000FF));
	}
	
	public static inline function ofRGBA(color:Int):Color {
		//0xRRGGBBAA
		return new Color(((color & 0xFF000000) >> 24),((color & 0x00FF0000) >> 16) ,((color & 0x0000FF00) >> 8),(color & 0x000000FF));
	}
	
	private function gdColor():Int {
		return ((((((red << 8) + green) << 8) + blue) << 8 ) + alpha);
	}

}
