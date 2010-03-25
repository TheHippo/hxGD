package hxGD;

import neko.Lib;

typedef PolygonPoint = {
	x : Int,
	y : Int
}

class Polygon {
	
	public var x(getX,null):Array<Int>;
	public var y(getY,null):Array<Int>;
	
	private var _x:Array<Int>;
	private var _y:Array<Int>;

	public function new() {
		_x = new Array<Int>();
		_y = new Array<Int>();
	}
	
	public inline function addPoint(x:Int,y:Int):Void {
		_x.push(x);
		_y.push(y);	
	}
	
	public inline function addPolygonPoint(p:PolygonPoint):Void {
		_x.push(p.x);
		_y.push(p.y);
	}
	
	private inline function getX():Array<Int> {
		return Lib.haxeToNeko(_x);
	}
	
	private inline function getY():Array<Int> {
		return Lib.haxeToNeko(_y);	
	}

}
