var app = angular.module('ngmain', ['ngRoute','ui.bootstrap']);

app.config(function($routeProvider){
  $routeProvider
    //the timeline display
    .when('/', {
      templateUrl: 'method.html',
      controller: 'mainController'
    })
    .when('/front', {
      templateUrl: 'front.html',
      controller: 'mainController'
    })
    .when('/frdenoise', {
      templateUrl: 'frdenoise.html',
      controller: 'mainController'
    })
    .when('/display', {
      templateUrl: 'display.html',
      controller: 'displayController'
    })
    .when('/cdisplay', {
      templateUrl: 'cdisplay.html',
      controller: 'cdisplayController'
    })
    .when('/denoise', {
      templateUrl: 'denoise.html',
      controller: 'denoiseController'
    })
    .when('/about', {
      templateUrl: 'about.html',
      controller: 'mainController'
    })

});

app.factory('wave', function () {
    var wave = {};

    return wave;
});

app.controller('mainController', function ($scope, $http, wave) {
    $scope.setTransform = function () {
        var value = $scope.transform;
        wave.transform = 0;

        if (value == "Discrete Wavelet Transform") {
            wave.transform = 1;
            location.href = '#/front';
        } else if (value == "Continuous Wavelet Transform") {
            wave.transform = 2;
            location.href = '#/front';
        } else if (value == "Wavelet Packet Transform") {
            wave.transform = 3;
            location.href = '#/front';
        } else if (value == "Wavelet Denoising" || value == "Wavelet Denoising (BETA)") {
            wave.transform = 4;
            location.href = '#/frdenoise';
        }


    }

    $scope.dataInput = function () {

        if (typeof $scope.inp1 == 'undefined') {
            alert("Please input a valid Data Vector.");
            return;
        }

        var x = $scope.inp1.valueOf().split(/[\s,;\t\r\n]+/);
        var i;
        var j = 0;

        for (var i = 0; i < x.length; i++) {
            if (!isNaN(parseFloat(x[i]))) {
                j = j + 1;
            }
        }

        wave.sigLength = j;
        wave.sigData = new Float64Array(j);

        j = 0;

        for (var i = 0; i < x.length; i++) {
            temp = parseFloat(x[i]);
            if (!isNaN(temp)) {
                wave.sigData[j] = temp;
                j = j + 1;
            }
        }
        //alert(wave.sigData[0]);
        if (wave.transform == 1) {
          location.href = '#/display';
        } else if (wave.transform == 2) {
          location.href = '#/cdisplay';
        } else if (wave.transform == 4) {
          location.href = '#/denoise';
        }
    }

    $scope.fileInput = function () {
        var fileinput = document.getElementById('finp1');

        var finp1 = fileinput.files[0];
        var reader = new FileReader();
        var temp = 3.14159;

        if (typeof finp1 == 'undefined') {
            alert("Please input a valid Data File. ");
            return;
        }

        reader.onerror = function (e) {
            switch (e.target.error.code) {
                case e.target.error.NOT_FOUND_ERR:
                    alert('File Not Found!');
                    break;
                case e.target.error.NOT_READABLE_ERR:
                    alert('File is not readable');
                    break;
                default:
                    alert('An error occurred reading this file.');
            };
            return;
        }


        reader.onload = function (e) {
            var x = reader.result.split(/[\s,;\t\r\n]+/);

            var j = 0;

            for (var i = 0; i < x.length; i++) {
                if (!isNaN(parseFloat(x[i]))) {
                    j = j + 1;
                }
            }

            wave.sigLength = j;
            wave.sigData = new Float64Array(j);

            j = 0;

            for (var i = 0; i < x.length; i++) {
                temp = parseFloat(x[i]);
                if (!isNaN(temp)) {
                    wave.sigData[j] = temp;
                    j = j + 1;
                }
            }

            /*
            var rm = x.length - j;
            if (rm > 0) {
            wave.sigData.splice(j, rm);
            }
            */
            if (wave.transform == 1) {
              location.href = '#/display';
            } else if (wave.transform == 2) {
              location.href = '#/cdisplay';
            } else if (wave.transform == 4) {
              location.href = '#/denoise';
            }
        }

        reader.readAsText(finp1);
    }

    $scope.testInput = function () {
        var value = $scope.tvalue;
        var urlx = null;
        var data;
        var temp = 3.14159;

        if (value == "ECG") {
            urlx = "https://raw.githubusercontent.com/rafat/rafat.github.io/master/sites/wavelib/data/ecg.txt";
        } else if (value == "Heavisine") {
            urlx = "https://raw.githubusercontent.com/rafat/rafat.github.io/master/sites/wavelib/data/heavisine.txt";
        } else if (value == "Piecewise Regular 256") {
            urlx = "https://raw.githubusercontent.com/rafat/rafat.github.io/master/sites/wavelib/data/pieceregular.txt";
        } else if (value == "Piecewise Regular 2048") {
            urlx = "https://raw.githubusercontent.com/rafat/rafat.github.io/master/sites/wavelib/data/pieceregular2048.txt";
        } else if (value == "Piecewise Polynomial") {
            urlx = "https://raw.githubusercontent.com/rafat/rafat.github.io/master/sites/wavelib/data/piecepoly.txt";
        } else if (value == "Noisy Bumps") {
            urlx = "https://raw.githubusercontent.com/rafat/rafat.github.io/master/sites/wavelib/data/noisybumps.txt";
        } else if (value == "Noisy Doppler") {
            urlx = "https://raw.githubusercontent.com/rafat/rafat.github.io/master/sites/wavelib/data/noisydoppler.txt";
        } else if (value == "Noisy Heavisine") {
            urlx = "https://raw.githubusercontent.com/rafat/rafat.github.io/master/sites/wavelib/data/noisyheavisine.txt";
        } else if (value == "Noisy Piecewise Polynomial") {
            urlx = "https://raw.githubusercontent.com/rafat/rafat.github.io/master/sites/wavelib/data/noisypiecepoly.txt";
        } else if (value == "Noisy Piecewise Regular") {
            urlx = "https://raw.githubusercontent.com/rafat/rafat.github.io/master/sites/wavelib/data/noisypieceregular.txt";
        } else if (value == "El Nino Data") {
            urlx = "https://raw.githubusercontent.com/rafat/rafat.github.io/master/sites/wavelib/data/sst_nino3.dat";
        } else {
            alert("Please Select A Signal To Proceed.");
        }


        $http({ method: 'GET', url: urlx }).
        then(function (response) {
            $scope.status = response.status;
            data = response.data;

            var x = data.split(/[\s,;\t\r\n]+/);
            var j = 0;

            for (var i = 0; i < x.length; i++) {
                if (!isNaN(parseFloat(x[i]))) {
                    j = j + 1;
                }
            }

            wave.sigLength = j;
            wave.sigData = new Float64Array(j);

            j = 0;

            for (var i = 0; i < x.length; i++) {
                temp = parseFloat(x[i]);
                if (!isNaN(temp)) {
                    wave.sigData[j] = temp;
                    j = j + 1;
                }
            }

            /*
            var rm = x.length - j;
            if (rm > 0) {
            wave.sigData.splice(j, rm);
            }
            */
            if (wave.transform == 1) {
              location.href = '#/display';
            } else if (wave.transform == 2) {
              location.href = '#/cdisplay';
            } else if (wave.transform == 4) {
              location.href = '#/denoise';
            }
        }, function (response) {
            $scope.data = response.data || "Request failed";
            $scope.status = response.status;
        });
    }
});

app.controller('displayController', function ($scope, $http, $modal, wave) {
    //console.log(wave.sigLength);
    var lbl = [];
    var sigData = [];
    $scope.MaxIter = 0;
    $scope.selected = {};
    $scope.wdisplays = [];
    for (var i = 0; i < wave.sigLength; ++i) {
        lbl[i] = i;
        sigData[i] = wave.sigData[i];
        //console.log(lbl[i]);
    }

    /*    g = new Dygraph(document.getElementById("graph1"),
                    lbl,
                 {
                     legend: 'always',
                     color: '#3399ff',
                     animatedZooms: true,
                     title: 'Input'
                 }
    );
    */
    var g = {
      x: lbl,
      y: sigData,
      type: 'scatter'
    }

    var gdata = [g];

    Plotly.newPlot('graph1',gdata);
    /*
    $http.get('data/wavedb.json').success(function (data) {
    $scope.wavedb = data;
    });console
    */
    $scope.wavedb = [
        {
            "id": "0",
            "family": "haar",
            "wavelets": [
                { "wavelet": "haar", "filtlength": "2" }
            ]
        }, {
            "id": "1",
            "family": "daubechies",
            "wavelets": [
                { "wavelet": "db1", "filtlength": "2" },
                { "wavelet": "db2", "filtlength": "4" },
                { "wavelet": "db3", "filtlength": "6" },
                { "wavelet": "db4", "filtlength": "8" },
                { "wavelet": "db5", "filtlength": "10" },
                { "wavelet": "db6", "filtlength": "12" },
                { "wavelet": "db7", "filtlength": "14" },
                { "wavelet": "db8", "filtlength": "16" },
                { "wavelet": "db9", "filtlength": "18" },
                { "wavelet": "db10", "filtlength": "20" },
                { "wavelet": "db11", "filtlength": "22" },
                { "wavelet": "db12", "filtlength": "24" },
                { "wavelet": "db13", "filtlength": "26" },
                { "wavelet": "db14", "filtlength": "28" },
                { "wavelet": "db15", "filtlength": "30" }
            ]
        }, {
            "id": "2",
            "family": "biorthogonal",
            "wavelets": [
                { "wavelet": "bior1.1", "filtlength": "2" },
                { "wavelet": "bior1.3", "filtlength": "6" },
                { "wavelet": "bior1.5", "filtlength": "10" },
                { "wavelet": "bior2.2", "filtlength": "6" },
                { "wavelet": "bior2.4", "filtlength": "10" },
                { "wavelet": "bior2.6", "filtlength": "14" },
                { "wavelet": "bior2.8", "filtlength": "18" },
                { "wavelet": "bior3.1", "filtlength": "4" },
                { "wavelet": "bior3.3", "filtlength": "8" },
                { "wavelet": "bior3.5", "filtlength": "12" },
                { "wavelet": "bior3.7", "filtlength": "16" },
                { "wavelet": "bior3.9", "filtlength": "20" },
                { "wavelet": "bior4.4", "filtlength": "10" },
                { "wavelet": "bior5.5", "filtlength": "12" },
                { "wavelet": "bior6.8", "filtlength": "18" }
            ]
        }, {
            "id": "3",
            "family": "coiflets",
            "wavelets": [
                { "wavelet": "coif1", "filtlength": "6" },
                { "wavelet": "coif2", "filtlength": "12" },
                { "wavelet": "coif3", "filtlength": "18" },
                { "wavelet": "coif4", "filtlength": "24" },
                { "wavelet": "coif5", "filtlength": "30" }
            ]
        }, {
            "id": "4",
            "family": "symmlets",
            "wavelets": [
                { "wavelet": "sym2", "filtlength": "4" },
                { "wavelet": "sym3", "filtlength": "6" },
                { "wavelet": "sym4", "filtlength": "8" },
                { "wavelet": "sym5", "filtlength": "10" },
                { "wavelet": "sym6", "filtlength": "12" },
                { "wavelet": "sym7", "filtlength": "14" },
                { "wavelet": "sym8", "filtlength": "16" },
                { "wavelet": "sym9", "filtlength": "18" },
                { "wavelet": "sym10", "filtlength": "20" }
            ]
        }

    ];

    $scope.methods = [
    {
        "id": "0",
        "method": "DWT (Symmetric)"
    }, {
        "id": "1",
        "method": "DWT (Periodic)"
    }, {
        "id": "2",
        "method": "SWT"
    }, {
        "id": "3",
        "method": "MODWT"
    }
    ];

    $scope.levels = [];


    $scope.getMaxIter = function () {
        var flength = $scope.selected.wavelet.filtlength;
        var slength = wave.sigLength;
        $scope.MaxIter = Math.floor(Math.log(slength / (flength - 1)) / Math.log(2.0));

        $scope.levels = [];
        for (var i = 0; i < $scope.MaxIter; i++) {
            $scope.levels[i] = i + 1;
        }
    }

    $scope.waveTest = function () {
        var method;
        var ext = "NULL";

        if (typeof $scope.selected.family == 'undefined' || typeof $scope.selected.wavelet == 'undefined' ||
        typeof $scope.selected.method == 'undefined' || typeof $scope.selected.level == 'undefined') {
            alert("Please Selct All Values : Family, Wavelet, Method and Levels");
            return;
        }

        if ($scope.selected.method.id == "0") {
            method = "dwt";
            ext = "sym";
        } else if ($scope.selected.method.id == "1") {
            method = "dwt";
            ext = "per";
        } else if ($scope.selected.method.id == "2") {
            method = "swt";
            ext = "per";
        } else if ($scope.selected.method.id == "3") {
            method = "modwt";
            ext = "per";
        }
        //console.log($scope.selected.family.family);
        if ($scope.selected.family.family == "biorthogonal" && method == "modwt") {
            alert("the Method MODWT is not implemented for biorthogonal wavelets");
            return;
        }

        //console.log(wave.sigData);

        var N = wave.sigLength;
        var flength = $scope.selected.wavelet.filtlength;
        var J = $scope.selected.level;
        //console.log(N,J);

        if (method == "swt") {
            var div = parseInt(Math.pow(2, J));
            if ((N % div) != 0) {
                alert("In SWT the data length should be divisible by 2^(Number of Decomposition Levels)");
                return;
            }
        }

        wave.length = new Int32Array(J + 2);
        wave.lenlength = J + 2;
        wave.filtlength = flength;
        wave.J = J;
        wave.method = method;
        wave.ext = ext;
        //wave.output = [];
        //wave.filters = [];
        wave.wname = $scope.selected.wavelet.wavelet;

        var outlength = Module.ccall('wtoutputlength', 'number', ['number', 'string', 'number', 'number', 'string'], [N, method, flength, J, ext]);
        wave.outLength = outlength;

        //console.log(wave.sigData, N, wave.wname, method, J, ext, wave.output, wave.length, wave.lenlength, wave.filters, flength);

        //wave.filters = new Float64Array(4*filtlength);

        var wave_transform = Module.cwrap('wave_transform', 'null', ['number', 'number', 'string', 'string', 'number', 'string', 'number', 'number', 'number']);
        //[wave.sigData, N, wave.wname, method, J, ext, wave.output, wave.length, wave.lenlength, wave.filters, flength]);

        //input signal on heap
        var inpdata = wave.sigLength * wave.sigData.BYTES_PER_ELEMENT;
        var inpPtr = Module._malloc(inpdata);
        var inpHeap = new Uint8Array(Module.HEAPU8.buffer, inpPtr, inpdata);
        inpHeap.set(new Uint8Array(wave.sigData.buffer));

        //output on heap
        var outdata = outlength * wave.sigData.BYTES_PER_ELEMENT;
        var outPtr = Module._malloc(outdata);
        var outHeap = new Uint8Array(Module.HEAPU8.buffer, outPtr, outdata);
        //inpHeap.set(new Uint8Array(wave.sigData.buffer));

        //filters
        var filtdata = 4 * flength * wave.sigData.BYTES_PER_ELEMENT;
        var filtPtr = Module._malloc(filtdata);
        var filtHeap = new Uint8Array(Module.HEAPU8.buffer, filtPtr, filtdata);
        //inpHeap.set(new Uint8Array(wave.sigData.buffer));

        //length vector
        var lendata = (J + 2) * wave.length.BYTES_PER_ELEMENT;
        var lenPtr = Module._malloc(lendata);
        var lenHeap = new Uint8Array(Module.HEAPU8.buffer, lenPtr, lendata);
        lenHeap.set(new Uint8Array(wave.length.buffer));

        wave_transform(inpHeap.byteOffset, N, wave.wname, method, J, ext, outHeap.byteOffset, lenHeap.byteOffset, filtHeap.byteOffset);

        wave.output = new Float64Array(outHeap.buffer, outHeap.byteOffset, outlength);
        wave.filter = new Float64Array(filtHeap.buffer, filtHeap.byteOffset, 4 * flength);
        wave.length = new Int32Array(lenHeap.buffer, lenHeap.byteOffset, J + 2);
        //console.log(wave.filter);
        //console.log(wave.length);

        Module._free(inpHeap.byteOffset);
        //Module._free(outHeap.byteOffset);
        //Module._free(filtHeap.byteOffset);
        //Module._free(lenHeap.byteOffset);

        $scope.wdisplays = new Array(J + 2);
        $scope.wdisplays[0] = "Full Decomposition";
        $scope.wdisplays[1] = "Approx at Level " + J;

        for (var i = 2; i < J + 2; i++) {
            $scope.wdisplays[i] = "Details at Level " + (J + 2 - i);
        }

        var trace = [];
        var lbl = [];
       

        for (var i = 0; i < wave.sigLength; ++i) {
            lbl[i] = i;
        }

        trace[0] = {
            x: lbl,
            y: [].slice.call(wave.sigData),
            name: 'Signal',
            yaxis: 'y3',
            type: 'scatter'
        };

        var namea = "Apprx "+J;

        if (method == "dwt") {
            var wreccoeff = Module.cwrap('wreccoeff','number',['string','number','number','string','number','number','number','number','number']);

            var coefflength = (J+1) * wave.sigLength;

            var coeffdata = coefflength * wave.sigData.BYTES_PER_ELEMENT;
            var coeffPtr = Module._malloc(coeffdata);
            var coeffHeap = new Uint8Array(Module.HEAPU8.buffer, coeffPtr, coeffdata);

            wreccoeff(method,outHeap.byteOffset, lenHeap.byteOffset,ext,J,filtHeap.byteOffset,flength,N,coeffHeap.byteOffset);

            wave.reccoeff = new Float64Array(coeffHeap.buffer, coeffHeap.byteOffset, coefflength);

            Module._free(outHeap.byteOffset);
            Module._free(filtHeap.byteOffset);
            Module._free(lenHeap.byteOffset);
            Module._free(coeffHeap.byteOffset);

            //console.log(sigAppx);

            trace[1] = {
                x: lbl,
                y: [].slice.call(wave.reccoeff.slice(0,wave.sigLength)),
                name: namea,
                yaxis: 'y2',
                type: 'scatter'
            };

            var iter = wave.sigLength;

            for(var j = J; j > 0;--j) {

                //for (var i = 0; i < wave.sigLength; ++i) {
                    //sigData[i] = wave.reccoeff[iter+i];
                //}

                var named = "Detail "+j;

                trace[J-j+2] = {
                    x: lbl,
                    y: [].slice.call(wave.reccoeff.slice(iter,iter+wave.sigLength)),
                    name: named,
                    yaxis: 'y1',
                    type: 'scatter'
                };

                iter += wave.sigLength;;
            }

    
        } else {

            Module._free(outHeap.byteOffset);
            Module._free(filtHeap.byteOffset);
            Module._free(lenHeap.byteOffset);

            wave.reccoeff = wave.output.slice();

            trace[1] = {
                x: lbl,
                y: [].slice.call(wave.output.slice(0,wave.sigLength)),
                name: namea,
                yaxis: 'y2',
                type: 'scatter'
            };

            var iter = wave.sigLength;

            for(var j = J; j > 0;--j) {

                //for (var i = 0; i < wave.sigLength; ++i) {
                    //sigData[i] = wave.reccoeff[iter+i];
                //}

                var named = "Detail "+j;

                trace[J-j+2] = {
                    x: lbl,
                    y: [].slice.call(wave.output.slice(iter,iter+wave.sigLength)),
                    name: named,
                    yaxis: 'y1',
                    type: 'scatter'
                };

                iter += wave.sigLength;;
            }
        }

        var layout = {
            yaxis3: {domain: [0.7,1],title: 'Signal'},
            legend: {traceorder: 'reversed'},
            yaxis2: {domain: [0.35, 0.65],title: 'Approximation'},
            yaxis1: {domain: [0, 0.3],title: 'Details'}
        };

        Plotly.newPlot('graph1',trace,layout);

        //var lbl = [];
        //var sigData = [];
        //for (var i = 0; i < wave.outLength; ++i) {
        //    lbl[i] = i;
        //    sigData[i] = wave.output[i];
        //}

        //var g = {
        //  x: lbl,
        //  y: sigData,
        //  type: 'scatter'
        //}

        //var gdata = [g];

        //Plotly.newPlot('graph1',gdata);
/*
        g = new Dygraph(document.getElementById("graph1"),
                    lbl,
                 {
                     legend: 'always',
                     color: '#3399ff',
                     animatedZooms: true,
                     title: 'Full Decomposition'
                 }
        );
*/
        document.getElementById("reportButton").disabled = false;

    }

    $scope.updateGraph = function () {
        //console.log($scope.selected.wdisplay);
        var trace = [];
        var lbl = [];
       var name1,name2;

        for (var i = 0; i < wave.sigLength; ++i) {
            lbl[i] = i;
        }

        trace[0] = {
            x: lbl,
            y: [].slice.call(wave.sigData),
            name: 'Signal',
            yaxis: 'y3',
            type: 'scatter'
        };
        var sigData = [];
        if ($scope.selected.wdisplay == 0) {
            name1 = 'Details';
            name2 = 'Approximation';
            if (wave.method == "dwt") {
    
                trace[1] = {
                    x: lbl,
                    y: [].slice.call(wave.reccoeff.slice(0,wave.sigLength)),
                    name: namea,
                    yaxis: 'y2',
                    type: 'scatter'
                };
    
                var iter = wave.sigLength;
    
                for(var j = wave.J; j > 0;--j) {
    
                    //for (var i = 0; i < wave.sigLength; ++i) {
                        //sigData[i] = wave.reccoeff[iter+i];
                    //}
    
                    var named = "Detail "+j;
    
                    trace[wave.J-j+2] = {
                        x: lbl,
                        y: [].slice.call(wave.reccoeff.slice(iter,iter+wave.sigLength)),
                        name: named,
                        yaxis: 'y1',
                        type: 'scatter'
                    };
    
                    iter += wave.sigLength;;
                }
    
        
            } else {
    
                trace[1] = {
                    x: lbl,
                    y: [].slice.call(wave.output.slice(0,wave.sigLength)),
                    name: namea,
                    yaxis: 'y2',
                    type: 'scatter'
                };
    
                var iter = wave.sigLength;
    
                for(var j = wave.J; j > 0;--j) {
    
                    //for (var i = 0; i < wave.sigLength; ++i) {
                        //sigData[i] = wave.reccoeff[iter+i];
                    //}
    
                    var named = "Detail "+j;
    
                    trace[wave.J-j+2] = {
                        x: lbl,
                        y: [].slice.call(wave.output.slice(iter,iter+wave.sigLength)),
                        name: named,
                        yaxis: 'y1',
                        type: 'scatter'
                    };
    
                    iter += wave.sigLength;;
                }
            }
        } else if ($scope.selected.wdisplay == 1) {
            var namea = "Approx.(Rec)";
            name2 = namea;
            trace[1] = {
                x: lbl,
                y: [].slice.call(wave.reccoeff.slice(0,wave.sigLength)),
                name: namea,
                yaxis: 'y2',
                type: 'scatter'
            };
            namea = "Approx.";
            name1 = namea;
            trace[2] = {
                x: lbl,
                y: [].slice.call(wave.output.slice(0,wave.length[0])),
                name: namea,
                yaxis: 'y1',
                type: 'scatter'
            };

        } else {
            var k = parseInt($scope.selected.wdisplay) - 1;
            var start_index = 0;
            var rstart_index = 0;
            for (var i = 0; i < k; i++) {
                start_index += wave.length[i];
                rstart_index += wave.sigLength;
            }
            var end_index = start_index + wave.length[k];
            var rend_index = rstart_index + wave.sigLength;

            var namea = "Detail(Rec)";
            name2 = namea;
            trace[1] = {
                x: lbl,
                y: [].slice.call(wave.reccoeff.slice(rstart_index,rend_index)),
                name: namea,
                yaxis: 'y2',
                type: 'scatter'
            };
            namea = "Detail";
            name1 = namea;
            trace[2] = {
                x: lbl,
                y: [].slice.call(wave.output.slice(start_index,end_index)),
                name: namea,
                yaxis: 'y1',
                type: 'scatter'
            };
            
        }

        var layout = {
            yaxis3: {domain: [0.7,1],title: 'Signal'},
            legend: {traceorder: 'reversed'},
            yaxis2: {domain: [0.35, 0.65],title: name2},
            yaxis1: {domain: [0, 0.3],title: name1}
        };

        Plotly.newPlot('graph1',trace,layout);
/*
        g = new Dygraph(document.getElementById("graph1"),
                    lbl,
                 {
                     legend: 'always',
                     color: '#3399ff',
                     animatedZooms: true,
                     title: $scope.wdisplays[parseInt($scope.selected.wdisplay)]
                 }
        );
        */
    }

    $scope.items = ['item1', 'item2', 'item3'];

    $scope.viewReport = function () {
        //window.open('#/report', '_blank');
        var modalInstance = $modal.open({
            templateUrl: 'myModalContent.html',
            controller: 'reportController',
            windowClass: 'large-Modal',
            resolve: {
                items: function () {
                    return $scope.items;
                }
            }
        });

        modalInstance.result.then(function (selectedItem) {
            $scope.selected = selectedItem;
        });

    }


});

app.controller('reportController', function ($scope, $modalInstance, items, wave) {
    //$scope.wname = wave.wname;
    $scope.wname = wave.wname;
    if (wave.method == "dwt") {
        $scope.method = "Discrete Wavelet Transform";
        if (wave.ext == "sym") {
            $scope.ext = "Symmetric Extension";
        } else {
            $scope.ext = "Periodic Extension";
        }
    } else if (wave.method == "swt") {
        $scope.method = "Stationary Wavelet Transform";
        $scope.ext = "Periodic Extension";
    } else if (wave.method == "modwt") {
        $scope.method = "Maximal Overlap Discrete Wavelet Transform";
        $scope.ext = "Periodic Extension";
    }

    $scope.flength = wave.filtlength;
    var fval = parseInt($scope.flength);
    $scope.J = wave.J;
    var J = parseInt(wave.J);

    $scope.lpd = [];
    $scope.hpd = [];
    $scope.lpr = [];
    $scope.hpr = [];

    for (var i = 0; i < fval; i++) {
        $scope.lpd[i] = wave.filter[i];
        $scope.hpd[i] = wave.filter[i + fval];
        $scope.lpr[i] = wave.filter[i + 2 * fval];
        $scope.hpr[i] = wave.filter[i + 3 * fval];
        //console.log(i + $scope.flength, i);
    }
    //console.log(wave.filter);
    //console.log(wave.length);
    $scope.length = wave.length;
    $scope.outlength = wave.outLength;
    $scope.appx = [];
    $scope.details = [];

    for (var i = 0; i < $scope.length[0]; i++) {
        $scope.appx[i] = wave.output[i];
    }
    var start = $scope.length[0];
    var end = start + $scope.length[1];
    for (var j = 0; j < J; j++) {
        var det = [];

        for (i = start; i < end; i++) {
            det[i - start] = wave.output[i];
        }
        start = end;
        end = start + $scope.length[j + 2];
        $scope.details.push(det);
    }

    //console.log($scope.details);

    $scope.items = items;
    $scope.selected = {
        item: $scope.items[0]
    };
    /*
    $scope.ok = function () {
        $modalInstance.close($scope.selected.item);
    };
    */
    $scope.cancel = function () {
        $modalInstance.dismiss('cancel');
    };
});

app.controller('denoiseController', function ($scope, $http, $modal, wave) {
    var lbl = [];
    var sigData = [];
    $scope.MaxIter = 0;
    $scope.selected = {};
    $scope.wdisplays = [];
    for (var i = 0; i < wave.sigLength; ++i) {
        lbl[i] = i;
        sigData[i] = wave.sigData[i];
    }

    var g = {
      x: lbl,
      y: sigData,
      type: 'scatter'
    }

    var gdata = [g];

    Plotly.newPlot('graph1',gdata);

    $scope.levels = [];


    $scope.getMaxIter = function () {
        var flength = $scope.selected.wavelet.filtlength;
        var slength = wave.sigLength;
        $scope.MaxIter = Math.floor(Math.log(slength / (flength - 1)) / Math.log(2.0));

        $scope.levels = [];
        for (var i = 0; i < $scope.MaxIter; i++) {
            $scope.levels[i] = i + 1;
        }
    }

    $scope.dnmethods = [
    {
        "id": "0",
        "dnmethod": "Sureshrink"
    }, {
        "id": "1",
        "dnmethod": "Visushrink"
    }
    ];

    $scope.thresholds = [
    {
        "id": "0",
        "threshold": "soft"
    }, {
        "id": "1",
        "threshold": "hard"
    }
    ];

    $scope.wavedb = [
        {
            "id": "0",
            "family": "haar",
            "wavelets": [
                { "wavelet": "haar", "filtlength": "2" }
            ]
        }, {
            "id": "1",
            "family": "daubechies",
            "wavelets": [
                { "wavelet": "db1", "filtlength": "2" },
                { "wavelet": "db2", "filtlength": "4" },
                { "wavelet": "db3", "filtlength": "6" },
                { "wavelet": "db4", "filtlength": "8" },
                { "wavelet": "db5", "filtlength": "10" },
                { "wavelet": "db6", "filtlength": "12" },
                { "wavelet": "db7", "filtlength": "14" },
                { "wavelet": "db8", "filtlength": "16" },
                { "wavelet": "db9", "filtlength": "18" },
                { "wavelet": "db10", "filtlength": "20" },
                { "wavelet": "db11", "filtlength": "22" },
                { "wavelet": "db12", "filtlength": "24" },
                { "wavelet": "db13", "filtlength": "26" },
                { "wavelet": "db14", "filtlength": "28" },
                { "wavelet": "db15", "filtlength": "30" }
            ]
        }, {
            "id": "2",
            "family": "biorthogonal",
            "wavelets": [
                { "wavelet": "bior1.1", "filtlength": "2" },
                { "wavelet": "bior1.3", "filtlength": "6" },
                { "wavelet": "bior1.5", "filtlength": "10" },
                { "wavelet": "bior2.2", "filtlength": "6" },
                { "wavelet": "bior2.4", "filtlength": "10" },
                { "wavelet": "bior2.6", "filtlength": "14" },
                { "wavelet": "bior2.8", "filtlength": "18" },
                { "wavelet": "bior3.1", "filtlength": "4" },
                { "wavelet": "bior3.3", "filtlength": "8" },
                { "wavelet": "bior3.5", "filtlength": "12" },
                { "wavelet": "bior3.7", "filtlength": "16" },
                { "wavelet": "bior3.9", "filtlength": "20" },
                { "wavelet": "bior4.4", "filtlength": "10" },
                { "wavelet": "bior5.5", "filtlength": "12" },
                { "wavelet": "bior6.8", "filtlength": "18" }
            ]
        }, {
            "id": "3",
            "family": "coiflets",
            "wavelets": [
                { "wavelet": "coif1", "filtlength": "6" },
                { "wavelet": "coif2", "filtlength": "12" },
                { "wavelet": "coif3", "filtlength": "18" },
                { "wavelet": "coif4", "filtlength": "24" },
                { "wavelet": "coif5", "filtlength": "30" }
            ]
        }, {
            "id": "4",
            "family": "symmlets",
            "wavelets": [
                { "wavelet": "sym2", "filtlength": "4" },
                { "wavelet": "sym3", "filtlength": "6" },
                { "wavelet": "sym4", "filtlength": "8" },
                { "wavelet": "sym5", "filtlength": "10" },
                { "wavelet": "sym6", "filtlength": "12" },
                { "wavelet": "sym7", "filtlength": "14" },
                { "wavelet": "sym8", "filtlength": "16" },
                { "wavelet": "sym9", "filtlength": "18" },
                { "wavelet": "sym10", "filtlength": "20" }
            ]
        }

    ];

    $scope.methods = [
    {
        "id": "0",
        "method": "DWT (Symmetric)"
    }, {
        "id": "1",
        "method": "DWT (Periodic)"
    }
    , {
        "id": "2",
        "method": "SWT"
    }
    ];

    $scope.denoiseSignal = function () {
        var method;
        var ext = "NULL";
        var noise_level;
        var dnmethod;
        var threshold;

        if (typeof $scope.selected.family == 'undefined' || typeof $scope.selected.wavelet == 'undefined' ||
        typeof $scope.selected.method == 'undefined' || typeof $scope.selected.dnmethod == 'undefined' ||
        typeof $scope.selected.threshold == 'undefined') {
            alert("Please Selct All Values : Family, Wavelet, Transform Method, denoising method and Thresholding");
            return;
        }

        if ($scope.selected.method.id == "0") {
            method = "dwt";
            ext = "sym";
        } else if ($scope.selected.method.id == "1") {
            method = "dwt";
            ext = "per";
        } else if ($scope.selected.method.id == "2") {
            method = "swt";
            ext = "per";
        }

        //console.log($scope.selected.dnmethod);
        if ($scope.selected.family.family == "biorthogonal" && method == "modwt") {
            alert("the Method MODWT is not implemented for biorthogonal wavelets");
            return;
        }


        dnmethod = $scope.selected.dnmethod.dnmethod;
        threshold = $scope.selected.threshold.threshold;

        //console.log(threshold);

        var N = wave.sigLength;
        var flength = $scope.selected.wavelet.filtlength;
        var J = $scope.selected.level;
        //console.log(wave.sigData);

        if (method == "swt") {
            var div = parseInt(Math.pow(2, J));
            if ((N % div) != 0) {
                alert("In SWT the data length should be divisible by 2^(Number of Decomposition Levels)");
                return;
            }
        }

        noise_level = "first"; //TODO : make it a selectable value - "first" or "all"
        wave.J = J;
        wave.method = method;
        wave.ext = ext;
        wave.dnmethod = dnmethod;
        wave.threshold = threshold;
        wave.noise_level = noise_level;
        //wave.output = [];
        //wave.filters = [];
        wave.wname = $scope.selected.wavelet.wavelet;


        //console.log(wave.sigData, N, wave.wname, method, J, ext, wave.output, wave.length, wave.lenlength, wave.filters, flength);


        var wave_denoise = Module.cwrap('wdenoise', 'null', ['number', 'number', 'number','string','string','string','string','string','string','number']);
        //[wave.sigData, N, wave.wname, method, J, ext, wave.output, wave.length, wave.lenlength, wave.filters, flength]);
        //[wave.sigData,N,J,wave.wname,method,ext,dnmethod.threshold,wave.denoised]
        //input signal on heap
        var inpdata = wave.sigLength * wave.sigData.BYTES_PER_ELEMENT;
        var inpPtr = Module._malloc(inpdata);
        var inpHeap = new Uint8Array(Module.HEAPU8.buffer, inpPtr, inpdata);
        inpHeap.set(new Uint8Array(wave.sigData.buffer));

        //output on heap
        var outdata = wave.sigLength  * wave.sigData.BYTES_PER_ELEMENT;
        var outPtr = Module._malloc(outdata);
        var outHeap = new Uint8Array(Module.HEAPU8.buffer, outPtr, outdata);
        //inpHeap.set(new Uint8Array(wave.sigData.buffer));

        //wave_transform(inpHeap.byteOffset, N, wave.wname, method, J, ext, outHeap.byteOffset, lenHeap.byteOffset, filtHeap.byteOffset);
        wave_denoise(inpHeap.byteOffset,N,J,dnmethod,wave.wname,method,ext,threshold,noise_level,outHeap.byteOffset)

        wave.denoised = new Float64Array(outHeap.buffer, outHeap.byteOffset, wave.sigLength);
        //console.log(wave.filter);

        Module._free(inpHeap.byteOffset);
        Module._free(outHeap.byteOffset);

        $scope.wdisplays = new Array(4);
        $scope.wdisplays[0] = "FULL VIEW";
        $scope.wdisplays[1] = "Input Signal";
        $scope.wdisplays[2] = "Denoised Signal";
        $scope.wdisplays[3] = "Noise";
        $scope.wdisplays[4] = "Superimposed View";

        var lbl = [];
        var sigData = [];
        var denoised = [];
        var noise = [];
        var trace = [];

        var ya = [];
        
        for(var i = 1; i < 4;++i) {
          ya[i-1] = "y"+i;
        }

        for (var i = 0; i < wave.sigLength; ++i) {
            lbl[i] = i;
            sigData[i] = wave.sigData[i];
        }

        trace[0] = {
            x: lbl,
            y: sigData,
            name: 'Signal',
            yaxis: ya[2],
            type: 'scatter'
        };

        for (var i = 0; i < wave.sigLength; ++i) {
            denoised[i] = wave.denoised[i];
        }

        trace[1] = {
            x: lbl,
            y: denoised,
            name: 'DeNoised',
            yaxis: ya[1],
            type: 'scatter'
        };

        for (var i = 0; i < wave.sigLength; ++i) {
            noise[i] = wave.sigData[i] - wave.denoised[i];
        }

        trace[2] = {
            x: lbl,
            y: noise,
            name: 'Noise',
            yaxis: ya[0],
            type: 'scatter'
        };

        var layout = {
            yaxis3: {domain: [0.7,1],title: 'Signal'},
            legend: {traceorder: 'reversed'},
            yaxis2: {domain: [0.35, 0.65],title: 'DeNoised'},
            yaxis1: {domain: [0, 0.3],title: 'Noise'}
          };

        Plotly.newPlot('graph1',trace,layout);
/*
        g = new Dygraph(document.getElementById("graph1"),
                    lbl,
                 {
                     legend: 'always',
                     color: '#3399ff',
                     animatedZooms: true,
                     title: 'Full Decomposition'
                 }
        );
*/
        document.getElementById("reportButton").disabled = false;

    }

    $scope.updateGraph = function () {
        //console.log($scope.selected.wdisplay);
        var lbl = [];
        var sigData = [];
        if ($scope.selected.wdisplay == 0) {
            var denoised = [];
            var noise = [];
            var trace = [];
    
            var ya = [];
            
            for(var i = 1; i < 4;++i) {
              ya[i-1] = "y"+i;
            }
    
            for (var i = 0; i < wave.sigLength; ++i) {
                lbl[i] = i;
                sigData[i] = wave.sigData[i];
            }
    
            trace[0] = {
                x: lbl,
                y: sigData,
                name: 'Signal',
                yaxis: ya[2],
                type: 'scatter'
            };
    
            for (var i = 0; i < wave.sigLength; ++i) {
                denoised[i] = wave.denoised[i];
            }
    
            trace[1] = {
                x: lbl,
                y: denoised,
                name: 'DeNoised',
                yaxis: ya[1],
                type: 'scatter'
            };
    
            for (var i = 0; i < wave.sigLength; ++i) {
                noise[i] = wave.sigData[i] - wave.denoised[i];
            }
    
            trace[2] = {
                x: lbl,
                y: noise,
                name: 'Noise',
                yaxis: ya[0],
                type: 'scatter'
            };
    
            var layout = {
                yaxis3: {domain: [0.7,1],title: 'Signal'},
                legend: {traceorder: 'reversed'},
                yaxis2: {domain: [0.35, 0.65],title: 'DeNoised'},
                yaxis1: {domain: [0, 0.3],title: 'Noise'}
              };
    
            Plotly.newPlot('graph1',trace,layout);

        }  else if ($scope.selected.wdisplay == 4) {
            var denoised = [];
    
            for (var i = 0; i < wave.sigLength; ++i) {
                lbl[i] = i;
                sigData[i] = wave.sigData[i];
            }
    
            trace1 = {
                x: lbl,
                y: sigData,
                name: 'Signal',
                type: 'scatter'
            };
    
            for (var i = 0; i < wave.sigLength; ++i) {
                denoised[i] = wave.denoised[i];
            }
    
            trace2 = {
                x: lbl,
                y: denoised,
                name: 'DeNoised',
                type: 'scatter'
            };

            var gdata = [trace1,trace2];

            Plotly.newPlot('graph1',gdata);

        } else {
            if ($scope.selected.wdisplay == 1) {
                for (var i = 0; i < wave.sigLength; ++i) {
                    lbl[i] = i ;
                    sigData[i] = wave.sigData[i];
                }
            } else if ($scope.selected.wdisplay == 2) {
                for (var i = 0; i < wave.sigLength; ++i) {
                    lbl[i] = i;
                    sigData[i] = wave.denoised[i];
                }
            } else if ($scope.selected.wdisplay == 3) {
                for (var i = 0; i < wave.sigLength; ++i) {
                    lbl[i] = i;
                    sigData[i] = wave.sigData[i] - wave.denoised[i];
                }
            } 
            var g = {
            x: lbl,
            y: sigData,
            type: 'scatter'
            }

            var gdata = [g];

            Plotly.newPlot('graph1',gdata);
        }

    }

    $scope.items = ['item1', 'item2', 'item3'];

    $scope.viewReport = function () {
        //window.open('#/report', '_blank');
        var modalInstance = $modal.open({
            templateUrl: 'myModalContent2.html',
            controller: 'dreportController',
            windowClass: 'large-Modal',
            resolve: {
                items: function () {
                    return $scope.items;
                }
            }
        });

        modalInstance.result.then(function (selectedItem) {
            $scope.selected = selectedItem;
        });

    }

});

app.controller('dreportController', function ($scope, $modalInstance, items, wave) {
    //$scope.wname = wave.wname;
    
    
    $scope.length = wave.sigLength;
    $scope.method = wave.method;
    $scope.ext = wave.ext;
    $scope.dnmethod = wave.dnmethod;
    $scope.threshold = wave.threshold;
    $scope.wname = wave.wname;
    $scope.level = wave.J;
    $scope.appx = [];

    for (var i = 0; i < $scope.length; i++) {
        $scope.appx[i] = wave.denoised[i];
    }

    //console.log($scope.details);

    $scope.items = items;
    $scope.selected = {
        item: $scope.items[0]
    };
    /*
    $scope.ok = function () {
        $modalInstance.close($scope.selected.item);
    };
    */
    $scope.cancel = function () {
        $modalInstance.dismiss('cancel');
    };
});

app.controller('cdisplayController', function ($scope, $http, wave) {
    //console.log(wave.sigLength);
    var lbl = [];
    var sigData = [];
    $scope.MaxIter = 0;
    $scope.selected = {};
    $scope.wdisplays = [];
    for (var i = 0; i < wave.sigLength; ++i) {
        lbl[i] = i;
        sigData[i] = wave.sigData[i];
        //console.log(lbl[i]);
    }

    /*    g = new Dygraph(document.getElementById("graph1"),
                    lbl,
                 {
                     legend: 'always',
                     color: '#3399ff',
                     animatedZooms: true,
                     title: 'Input'
                 }
    );
    */
    var g = {
      x: lbl,
      y: sigData,
      type: 'scatter'
    }

    var gdata = [g];

    Plotly.newPlot('graph1',gdata);

    $scope.cwavedb = [
        {
            "id": "0",
            "family": "Morlet"
        }, {
            "id": "1",
            "family": "Paul"
        }, {
            "id": "2",
            "family": "Dog",
        }

    ];


    $scope.stype = [
        {
            "id": "0",
            "type": "Power of 2"
        }, {
            "id": "1",
            "type": "Linear"
        }

    ];

    $scope.cmap = [
        {
            "id": "0",
            "cscale": "RdBu"
        }, {
            "id": "1",
            "cscale": "Earth"
        }, {
            "id": "2",
            "cscale": "Blackbody",
        }, {
            "id": "3",
            "cscale": "YIOrRd",
        }, {
            "id": "4",
            "cscale": "YIGnBu",
        }, {
            "id": "5",
            "cscale": "Bluered",
        }, {
            "id": "6",
            "cscale": "Portland",
        }, {
            "id": "7",
            "cscale": "Electric",
        }, {
            "id": "8",
            "cscale": "Jet",
        }, {
            "id": "9",
            "cscale": "Hot",
        }, {
            "id": "10",
            "cscale": "Greys",
        }, {
            "id": "11",
            "cscale": "Greens",
        }, {
            "id": "12",
            "cscale": "Picnic",
        }

    ];

    $scope.caxis = [
        {
            "id": "0",
            "yaxis": "Scale"
        }, {
            "id": "1",
            "yaxis": "Period"
        }, {
            "id": "2",
            "yaxis": "Frequency"
        }

    ];



    $scope.cwaveTest = function () {

        if (typeof $scope.selected.family == 'undefined' || typeof $scope.selected.type == 'undefined' || typeof $scope.selected.cscale == 'undefined'
      || typeof $scope.selected.yaxis == 'undefined') {
            alert("Please Selct All Values : Wavelet, ColorMap, Y Axis and Scale Type");
            return;
        }

        if (isNaN($scope.dt) || isNaN($scope.jtot) || isNaN($scope.dj) || isNaN($scope.s0) || isNaN($scope.param)) {
          alert("Sampling Period, Parameter and Scale Settings only accept numerical values");
        }

        if ($scope.dt <= 0 || $scope.jtot <= 0 || $scope.dj <= 0 || $scope.s0 <= 0 || $scope.param <= 0) {
          alert("Sampling Period, Parameter and Scale Settings only accept positive values");
        }

        if ($scope.selected.family.id == 0 ) {
          wave.wname = "morlet";
        }

        if ($scope.selected.family.id == 1 ) {
          var prm = $scope.param;
          if (parseInt(prm,10) != prm || prm > 20) {
            alert("Paul Wavelet only accepts integer values <= 20")
          }
          wave.wname = "paul";
        }
        if ($scope.selected.family.id == 2 ) {
          var prm = ($scope.param) / 2;
          if (parseInt(prm,10) != prm ) {
            alert("Derivative of Gaussian Wavelet only accepts even integer values")
          }
          wave.wname = "dgauss";
        }

        if ($scope.selected.type.id == 0) {
          wave.type = "power";
        } else {
          wave.type = "linear";
        }

        wave.param = $scope.param;
        wave.dt = $scope.dt;
        wave.J = $scope.jtot;
        wave.dj = $scope.dj;
        wave.s0 = $scope.s0;

        var N = wave.sigLength;
        var power = 2;
        var npflag = 1;
        var outlength = wave.sigLength * wave.J;

        var cwave_transform = Module.cwrap('cwave_transform', 'null', ['string', 'number', 'number', 'number','number',
        'number', 'number', 'number','string','number','number','number','number','number','number','number']);

        //input signal on heap
        var inpdata = wave.sigLength * wave.sigData.BYTES_PER_ELEMENT;
        var inpPtr = Module._malloc(inpdata);
        var inpHeap = new Uint8Array(Module.HEAPU8.buffer, inpPtr, inpdata);
        inpHeap.set(new Uint8Array(wave.sigData.buffer));

        //output (Absolute Magnitude) on heap
        var outputdata = outlength * wave.sigData.BYTES_PER_ELEMENT;
        var outputPtr = Module._malloc(outputdata);
        var outputHeap = new Uint8Array(Module.HEAPU8.buffer, outputPtr, outputdata);

        //Scale vector on heap
        var scaledata = wave.J * wave.sigData.BYTES_PER_ELEMENT;
        var scalePtr = Module._malloc(scaledata);
        var scaleHeap = new Uint8Array(Module.HEAPU8.buffer, scalePtr, scaledata);

        //Period vector on heap
        var perioddata = wave.J * wave.sigData.BYTES_PER_ELEMENT;
        var periodPtr = Module._malloc(perioddata);
        var periodHeap = new Uint8Array(Module.HEAPU8.buffer, periodPtr, perioddata);

        //COI vector on heap
        var coidata = wave.sigLength * wave.sigData.BYTES_PER_ELEMENT;
        var coiPtr = Module._malloc(coidata);
        var coiHeap = new Uint8Array(Module.HEAPU8.buffer, coiPtr, coidata);

        /*
        void cwave_transform(char* wave, double param, double *inp, int N,double dt, int J,double s0, double dj, char *type, int power,
        int npflag, double *oupre, double *oupim,double *scale, double *period, double *coi)
        */

        cwave_transform(wave.wname,wave.param,inpHeap.byteOffset,wave.sigLength,wave.dt,wave.J,wave.s0,wave.dj,wave.type,power,
          npflag,outputHeap.byteOffset,scaleHeap.byteOffset,periodHeap.byteOffset,coiHeap.byteOffset);

        wave.output = new Float64Array(outputHeap.buffer, outputHeap.byteOffset, outlength);
        wave.scale = new Float64Array(scaleHeap.buffer, scaleHeap.byteOffset, wave.J);
        wave.period = new Float64Array(periodHeap.buffer, periodHeap.byteOffset, wave.J);
        wave.coi = new Float64Array(coiHeap.buffer, coiHeap.byteOffset, wave.sigLength);

        //console.log(wave.filter);
        //console.log(wave.scale);

        Module._free(inpHeap.byteOffset);
        Module._free(outputHeap.byteOffset);
        Module._free(scaleHeap.byteOffset);
        Module._free(periodHeap.byteOffset);
        Module._free(coiHeap.byteOffset);

        $scope.wdisplays = new Array(2);
        $scope.wdisplays[0] = "Input Signal";
        $scope.wdisplays[1] = "CWT Decomposition";

        $scope.x = new Array(wave.sigLength), $scope.y = new Array(wave.J);
        $scope.z = new Array(wave.J, $scope.tval = new Array(wave.J));
        var i, j,iter;
        if ($scope.selected.yaxis.id == 0) {
          $scope.yaxis = 'Scale';
          for (i = 0; i < wave.J; ++i) {
            $scope.y[i] = wave.scale[i];
            $scope.z[i] = new Array(wave.sigLength);
          }
        } else if ($scope.selected.yaxis.id == 1) {
          $scope.yaxis = 'Period';
          for (i = 0; i < wave.J; ++i) {
            $scope.y[i] = wave.period[i];
            $scope.z[i] = new Array(wave.sigLength);
          }
        } else if ($scope.selected.yaxis.id == 2) {
          $scope.yaxis = 'Frequency';
          for (i = 0; i < wave.J; ++i) {
            $scope.y[i] = 1.0 / wave.period[i];
            $scope.z[i] = new Array(wave.sigLength);
          }
        }

        for(i = 0; i < wave.sigLength;++i) {
          $scope.x[i] = i;
        }
        for (i = 0; i < wave.J; ++i) {
          iter = i * wave.sigLength;
          for(j = 0; j < wave.sigLength;++j) {
            $scope.z[i][j] = wave.output[iter+j] ;
          }
        }

        $scope.setColormap();

    }

    $scope.setDefault = function() {

    }

    $scope.setColormap = function() {

      var gdata = [ {
          z: $scope.z,
          x: $scope.x,
          y: $scope.y,
          colorscale: $scope.selected.cscale.cscale,
          zsmooth: 'best',
          type: 'heatmap'
         }
       ];
       if (typeof $scope.selected.type != 'undefined') {
          if ($scope.selected.type.id == 0) {
            var layout = {
              title : 'Power Spectrum',
              yaxis : {
                title : $scope.yaxis,
                type : 'log',
                dtick : 0.30102999566
              }
            }
          } else {
            var layout = {
              title : 'Power Spectrum',
              yaxis : {
                title : $scope.yaxis
              }
            }
          }
        }

       Plotly.newPlot('graph1', gdata,layout);
    }

    $scope.updateGraph = function () {
        //console.log($scope.selected.wdisplay);
        var lbl = [];
        var sigData = [];
        var sc = [];
        if ($scope.selected.wdisplay == 0) {
            for (var i = 0; i < wave.sigLength; ++i) {
                lbl[i] = i ;
                sigData[i] = wave.sigData[i];
            }
            var g = {
              x: lbl,
              y: sigData,
              type: 'scatter'
            }

            var gdata = [g];

            Plotly.newPlot('graph1',gdata);
        } else if ($scope.selected.wdisplay == 1) {

            $scope.setColormap();

        }

    }

  });

app.controller("TabsController", function ($scope, $window) {

});
