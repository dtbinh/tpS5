package jadelex;


public class Move extends BaseToken{
	private jade.Direction dir;

	public Move(jade.Direction d){
		super(TokenType.MOVE);
		dir = d;
	}
	
	public jade.Direction getDirection(){
		return dir;
	}

}
