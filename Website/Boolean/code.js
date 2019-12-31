var width = 15;
var height = 15;
var set = new Set();

setBoard();

function setBoard(){

	for(var i=0; i<height; i++){
		var row = document.createElement("div");
		row.classList = "row"
		for(var j=0; j<width; j++){
			var square = document.createElement("div");
			square.classList = "square";
            square.id = i*width + j;
			row.appendChild(square);
		}
		document.getElementById('matrix').appendChild(row);
	}
    console.log(  $("#matrix") );
    
}

$('.square').click(function() {
                   
	if($(this).css("background-color") === "rgb(255, 255, 255)"){
		$(this).css('background-color', 'black');
		set.add(this.id);
	}
	else{
		$(this).css('background-color', 'white');
		set.delete(this.id);
	}
});

$('#getCode').click(function(){
	
	var code = "{{";

	for(var i=0; i<height*width; i++){

		console.log( $("#" + i).css("background-color"));

		if( $("#" + i).css("background-color") == "rgb(255, 255, 255)")
			code += "0";
		else
			code += "1";
                    
        if(i%width == width-1)
            code += ",0,-1}, {";
        else
            code += ",";

	}

    code = code.substring(0, code.length - 3);
    code += "},";
    console.log(code);
                    
    $("#code").val(code);
});
