let width = 30;
let height = 30;
let color_history_size = 6;
var color_history_array = []
let suggeested_colors_size = 6;
let suggeested_colors_array = ["#000000", "#FFFFFF", "#FF0000", "#00FF00", "#0000FF", "#FFFF00"];
var frames = []

var set = new Set();

setBoard();

function setBoard(){

    // Set matrix
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
    
    // Set color history
    for(var i=0; i<color_history_size; i++){
        let color_history = document.createElement("div");
        color_history.classList = "color";
        color_history.id = "colorHistory" + i;
        console.log(color_history.id)
        
        color_history_array.push("#ffffff")
        
        document.getElementById('colorHistory').appendChild(color_history);
    }
    
    // Set suggeested colors
    for(var i=0; i<suggeested_colors_size; i++){
        let suggeested_colors = document.createElement("div");
        suggeested_colors.classList = "color";
        suggeested_colors.id = "suggeestedColors" + i;
        suggeested_colors.style.backgroundColor = suggeested_colors_array[i];
        
        document.getElementById('suggeestedColors').appendChild(suggeested_colors);
    }
}

$('.square').click(function() {
    $(this).css('background-color', $("#currrentColor").css('backgroundColor'));
    $("#clicked").css('background-color', $(this).css('backgroundColor'));
});

$('.color').click(function() {
    updateCurrentColor(this.id)
});

$('#selectColorWheel').click(function(){
    updateCurrentColor("colorWheel")
});

$('#getCode').click(function(){
	
	var code = "{{";

	for(var i=0; i<height*width; i++){
        
        code += rgbToHex("#" + i);
                
        if(i%width == width-1)
            code += "},{";
        else
            code += ",";
	}

    code = code.substring(0, code.length - 3);
    code += "},";
                    
    $("#code").val(code);
});

function updateCurrentColor(id){
    id = "#" + id
    let color = rgbToHex(id)
    
    if(id == "#colorWheel"){
        $("#currrentColor").css('background-color', $("#" + "colorWheel").val());
    }else{
        $("#currrentColor").css('background-color', $(id).css('backgroundColor'));
    }
    
    let index = color_history_array.indexOf(color)
    console.log(index)
    
    if(index == -1)
        
    for(var i=color_history_size-1; i>0; i--){
        let temp_color = $("#colorHistory" + (i-1)).css("background-color");
        $("#colorHistory"+i).css('background-color', temp_color);

        color_history_array[i-1] = color_history_array[i]
    }
    
    $("#colorHistory0").css('background-color', color);
}

function rgbToHex(id){
    
    var rgb = $(id).css('backgroundColor').match(/\d+/g);
    console.log(rgb)
    var hex = '#'+ String('0' + Number(rgb[0]).toString(16)).slice(-2) + String('0' + Number(rgb[1]).toString(16)).slice(-2) + String('0' + Number(rgb[2]).toString(16)).slice(-2);
    return hex;
}
