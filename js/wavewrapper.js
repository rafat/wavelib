var flength = function (str) {
    filtlength = Module.cwrap('filtlength', 'number', ['string']);
    return filtlength(str);
};

function zeroArray(length) {
    var array = [];
    for (var i = 0; i < length; i++) {
        array[i] = 0;
    }
    return array;
}

function sigdata() {
    var sigdata = [  -18.3237,-18.2232,-18.0974,-17.9410,-17.7480,-17.5113,-17.2230,-16.8744,-16.4558,-15.9565,-15.3653,-14.6701,-13.8586,-12.9182,
            -11.8363,-10.6008,-9.2006,-7.6257,-5.8680,-3.9217,-1.7839,0.5452,3.0614,5.7562,8.6167,11.6252,14.7591,17.9909,21.2884,24.6155,27.9319,
            31.1947,34.3587,37.3775,40.2049,42.7957,13.2164,14.2125,15.0317,15.6595,16.0845,16.2990,16.2990,16.0845,15.6595,15.0317,14.2125,13.2164,
            12.0608,10.7654,9.3517,34.3587,31.1947,27.9319,24.6155,21.2884,17.9909,14.7591,11.6252,8.6167,5.7562,3.0614,0.5452,-1.7839,-3.9217,-5.8680,
            -7.6257,-9.2006,-10.6008,-11.8363,-12.9182,-13.8586,-14.6701,-15.3653,-15.9565,-16.4558,-16.8744,-17.2230,-17.5113,-17.7480,-17.9410,-18.0974,
            -18.2232,-18.3237,-18.4035,-18.0080,-17.8889,-17.7403,-17.5533,-17.3156,-17.0102,-16.6129,-16.0884,-15.3848,-14.4239,-13.0840,-11.1708,-8.3634,
            -4.1098,2.5833,13.6048,32.7934,28.0187,10.9660,1.0776,-4.9459,-8.7354,-11.1225,-12.4865,-12.8019,-11.2050,-3.3124,1.8995,-11.3573,-15.0684,
            -16.5028,-17.1937,-17.5831,-17.8288,-17.9968,-18.1185,-18.2103,-18.2818,-18.3388,-18.3849,-18.4229,-18.4545,-18.4810,-17.4642,-17.2104,-16.9033,
            -16.5317,-16.0822,-15.5384,-14.8804,-14.0844,-13.1214,-11.9563,-10.5467,-8.8414,-6.7782,-4.2822,-1.2624,2.3911,6.8111,12.1585,18.6280,26.4549,
            35.9241,35.9241,26.4549,18.6280,12.1585,6.8111,2.3911,-1.2624,-4.2822,-6.7782,-8.8414,-10.5467,-11.9563,-13.1214,-14.0844,-14.8804,-15.5384,
            -16.0822,-16.5317,-16.9033,-17.2104,-17.4642,-18.6741,-18.6741,-18.6741,-18.6741,-18.6741,-18.6741,-18.6741,-18.6741,-18.6741,-18.6741,-18.6741,
            -18.6741,6.3259,6.3259,6.3259,6.3259,6.3259,6.3259,6.3259,6.3259,6.3259,6.3259,6.3259,6.3259,6.3259,6.3259,6.3259,6.3259,6.3259,6.3259,6.3259,
            6.3259,6.3259,6.3259,6.3259,6.3259,34.8066,34.6752,34.5285,34.3645,34.1812,33.9763,33.7474,33.4917,33.2058,32.8863,32.5294,32.1304,31.6846,31.1864,
            30.6296,30.0074,29.3121,28.5350,27.6667,26.6963,25.6118,24.3999,23.0456,21.5322,19.8408,17.9507,15.8385,13.4781,10.8403,7.8925,4.5982,0.9168,-3.1972,
            -7.7947,-12.932,-18.6741,-18.6741,-18.6741,-18.6741,-18.6741,-18.6741,-18.6741,-18.6741,-18.6741,-18.6741,-18.6741,-18.6741,-18.6741,-18.6741,-18.3237];
  return sigdata;
}

var fcoef = function (str) {
    fcoef = Module.cwrap('filtcoef', 'number', ['string', 'number', 'number', 'number', 'number']);
    var length = flength(str);
    var lpd = new Float64Array(length);
    var hpd = new Float64Array(length);
    var lpr = new Float64Array(length);
    var hpr = new Float64Array(length);
    var lbl = new Uint8Array(length);
    for (var i = 0; i < length; ++i) {
        lpd[i] = hpd[i] = lpr[i] = hpr[i] = 0.0;
        lbl[i] = i;
    }
    var size = 8 * length;
    var ptr1 = Module._malloc(size);
    var ptr2 = Module._malloc(size);
    var ptr3 = Module._malloc(size);
    var ptr4 = Module._malloc(size);
    var buf1 = new Uint8Array(Module.HEAPU8.buffer, ptr1, size);
    var buf2 = new Uint8Array(Module.HEAPU8.buffer, ptr2, size);
    var buf3 = new Uint8Array(Module.HEAPU8.buffer, ptr3, size);
    var buf4 = new Uint8Array(Module.HEAPU8.buffer, ptr4, size);
    buf1.set(new Uint8Array(lpd.buffer));
    buf2.set(new Uint8Array(hpd.buffer));
    buf3.set(new Uint8Array(lpr.buffer));
    buf4.set(new Uint8Array(hpr.buffer));
    var t = fcoef(str, buf1.byteOffset, buf2.byteOffset, buf3.byteOffset, buf4.byteOffset);
    var lpd = new Float64Array(buf1.buffer, buf1.byteOffset, length);
    var hpd = new Float64Array(buf2.buffer, buf2.byteOffset, length);
    var lpr = new Float64Array(buf3.buffer, buf3.byteOffset, length);
    var hpr = new Float64Array(buf4.buffer, buf4.byteOffset, length);

    Module._free(buf1);
    Module._free(buf2);
    Module._free(buf3);
    Module._free(buf4);
    console.log(lpd);
    console.log(hpd);
    console.log(lpr);
    console.log(hpr);

    $('#canvas-holder').append("<div class='row' />");
    $('#canvas-holder').append("<div class='row' />");

    for (var i = 0; i < 2; ++i) {
        $('.row').append("<div class='col-md-6' />");
    }

    var newCanvas = $('<canvas/>',{
                    id: 'canvas1'                   
                });
    $('.col-md-6:eq(0)').append(newCanvas);

    var newCanvas2 = $('<canvas/>',{
                    id: 'canvas2'                   
                });
    $('.col-md-6:eq(1)').append(newCanvas2);

    var newCanvas3 = $('<canvas/>',{
                    id: 'canvas3'                   
                });
    $('.col-md-6:eq(2)').append(newCanvas3);

    var newCanvas4 = $('<canvas/>',{
                    id: 'canvas4'                   
                });
    $('.col-md-6:eq(3)').append(newCanvas4);

    var barChartData = {
        labels: lbl,
        datasets: [
			{
			    fillColor: "rgba(255,0,0,0.5)",
			    strokeColor: "rgba(255,0,0,0.8)",
			    highlightFill: "rgba(255,0,0,0.75)",
			    highlightStroke: "rgba(255,0,0,1)",
			    data: lpd
			},

		]

    }

    var barChartData2 = {
        labels: lbl,
        datasets: [
			{
			    fillColor: "rgba(0,0,255,0.5)",
			    strokeColor: "rgba(0,0,255,0.8)",
			    highlightFill: "rgba(0,0,255,0.75)",
			    highlightStroke: "rgba(0,0,255,1)",
			    data: hpd
			},

		]

    }

    var barChartData3 = {
        labels: lbl,
        datasets: [
			{
			    fillColor: "rgba(255,0,0,0.5)",
			    strokeColor: "rgba(255,0,0,0.8)",
			    highlightFill: "rgba(255,0,0,0.75)",
			    highlightStroke: "rgba(255,0,0,1)",
			    data: lpr
			},

		]

    }

    var barChartData4 = {
        labels: lbl,
        datasets: [
			{
			    fillColor: "rgba(0,0,255,0.5)",
			    strokeColor: "rgba(0,0,255,0.8)",
			    highlightFill: "rgba(0,0,255,0.75)",
			    highlightStroke: "rgba(0,0,255,1)",
			    data: hpr
			},

		]

    }

    window.onload = function () {
        var ctx = document.getElementById("canvas1").getContext("2d");
        window.myBar = new Chart(ctx).Bar(barChartData, {
            responsive: true
        });
        var ctx2 = document.getElementById("canvas2").getContext("2d");
        window.myBar = new Chart(ctx2).Bar(barChartData2, {
            responsive: true
        });
        var ctx3 = document.getElementById("canvas3").getContext("2d");
        window.myBar = new Chart(ctx3).Bar(barChartData3, {
            responsive: true
        });
        var ctx4 = document.getElementById("canvas4").getContext("2d");
        window.myBar = new Chart(ctx4).Bar(barChartData4, {
            responsive: true
        });
    }
}

var frontpage = function () {
    //$('#canvas-holder').append("<img src='img/3dgausswave.png' />");
    $('#canvas-holder').append("<div class='row' />");
    //$('#canvas-holder').append("<div class='row' />");
    //for (var i = 0; i < 2; ++i) {
    //  $('.row').append("<div class='col-md-6' />");
    //}
    //$('.col-md-6').append("<img src='img/3dgauss.jpg' />");
    //$row.append("<div class='col-md-6' />").append("<img src='img/3dgauss.jpg' />");
    $('.row').append("<div class='col-md-3' />");
    $('.row').append("<div class='col-md-6' />");
    $('.row').append("<div class='col-md-3' />");
    var sig = sigdata();
    var length = sig.length;
    var lbl = [];

    for (i = 0; i < length; ++i) {
        lbl[i] = i;
    }

    var sigChartData = {
        labels: lbl,
        datasets: [
			{
			    label: "Input Signal",
                fillColor: "rgba(151,187,205,0.2)",
                strokeColor: "rgba(151,187,205,1)",
                pointColor: "rgba(151,187,205,1)",
                pointStrokeColor: "#fff",
                pointHighlightFill: "#fff",
                pointHighlightStroke: "rgba(151,187,205,1)",
			    data: sig
			},

		]

    }

    var newCanvas = $('<canvas/>',{
                    id: 'canvas1'                   
                });
    $('.col-md-6').append(newCanvas);

   window.onload = function () {
        var ctx = document.getElementById("canvas1").getContext("2d");
        window.myBar = new Chart(ctx).Line(sigChartData, {
            responsive: true
        });
   }

}

var frontpage2 = function () {
    //$('#canvas-holder').append("<img src='img/3dgausswave.png' />");
    $('#canvas-holder').append("<div class='row' />");
    //$('#canvas-holder').append("<div class='row' />");
    //for (var i = 0; i < 2; ++i) {
    //  $('.row').append("<div class='col-md-6' />");
    //}
    //$('.col-md-6').append("<img src='img/3dgauss.jpg' />");
    //$row.append("<div class='col-md-6' />").append("<img src='img/3dgauss.jpg' />");
    $('.row').append("<div class='col-md-4' />");
    $('.row').append("<div class='col-md-4' />");
    $('.row').append("<div class='col-md-4' />");
    var sig = sigdata();
    var length = sig.length;
    var lbl = [];

    for (i = 0; i < length; ++i) {
        lbl[i] = [i, sig[i]];
    }
    $('.starter-template').empty();
    $('.starter-template').append("<div id='graph' style='margin:0 auto' />");

    g = new Dygraph(document.getElementById("graph"),
                    lbl,
                 {
                     legend: 'always',
                     color: '#3399ff',
                     animatedZooms: true,
                     title: 'Input'
                 });

    $('.col-md-4:eq(0)').append("<div class='input-group' />");
    $('.input-group').append("<input type='text' class='form-control' placeholder='Paste Data....' />");
    $('.input-group').append("<span class='input-group-btn' />");
    $('.input-group-btn').append("<button class='btn btn-default' type='button' value='GO'>GO</button>");

    $('.col-md-4:eq(1)').append("<form role='form' class='form1' />");
    $('.form1').append("<div class='form-group' />");
    $('.form-group').append("<label />").text("Wavelet Family");

}

var displayPage = function() {
    //window.open('display.html','_self');
    document.location.href = 'display.html';
    $(document).ready(function() {
        var lbl = [];
        for (i = 0; i < wave.sigLength; ++i) {
            lbl[i] = [i, wave.sigData[i]];
        }
        console.log(lbl[0]);
        alert("Page Changed");
        g = new Dygraph(document.getElementById("graph1"),
                    lbl,
                 {
                     legend: 'always',
                     color: '#3399ff',
                     animatedZooms: true,
                     title: 'Input'
                 }
        );
    });
    
    
}