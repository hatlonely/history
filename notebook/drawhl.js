window.onload = drawhl;

function drawhl() {
    var canvas = document.createElement('canvas');
    var img = document.getElementById('hatlonely');
    canvas.width = 700;
    canvas.height = 30;
    var ctx = canvas.getContext('2d');
    // var color1 = '#C0F449';
    // var color2 = '#4C7123';
    // var color1 = '#00FF80';
    // var color2 = '#E9F01D';
    // var color1 = '#DEA681';
    // var color2 = '#483C32';
    var color1 = '#FFF100';
    var color2 = '#00849C';

    function drawCharL(color) {
        ctx.beginPath();
        ctx.moveTo(0, 0);
        ctx.lineTo(0, 30);
        ctx.lineTo(18, 30);
        ctx.lineTo(18, 18);
        ctx.lineTo(12, 18);
        ctx.lineTo(12, 24);
        ctx.lineTo(6, 24);
        ctx.lineTo(6, 3);
        ctx.lineTo(11, 0);
        ctx.closePath();
        ctx.fillStyle = color;
        ctx.fill();
    }

    function drawColor(color) {
        ctx.fillStyle = color;
        ctx.fillRect(0, 0, (canvas.width - canvas.height) / 2, 30);
    }

    function drawColorL(color) {
        ctx.save();
        drawColor(color);
        ctx.restore();
    }

    function drawColorR(color) {
        ctx.save();
        ctx.translate((canvas.width + canvas.height) / 2, 0);
        drawColor(color);
        ctx.restore();
    }

    function drawCharLL(color) {
        ctx.save();
        ctx.translate((canvas.width - canvas.height) / 2, 0);
        drawCharL(color);
        ctx.restore();
    }

    function drawCharLR(color) {
        ctx.save();
        ctx.translate((canvas.width + canvas.height) / 2, 30);
        ctx.rotate(Math.PI);
        drawCharL(color);
        ctx.restore();
    }

    drawColorL(color1);
    drawColorR(color2);
    drawCharLL(color2);
    drawCharLR(color1);

    img.src = canvas.toDataURL("image/png");
}