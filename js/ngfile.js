var app = angular.module('ngmain', ['ngRoute','ui.bootstrap']);

app.config(function($routeProvider){
  $routeProvider
    //the timeline display
    .when('/', {
      templateUrl: 'front.html',
      controller: 'mainController'
    })
    .when('/display', {
      templateUrl: 'display.html',
      controller: 'displayController'
    })
    .when('/about', {
      templateUrl: 'about.html',
      controller: 'mainController'
    })
    .when('/demos', {
      templateUrl: 'demos.html',
      controller: 'mainController'
    })
    
   
});

app.factory('wave', function () {
    var wave = {};
    
    return wave;
});

/*
app.directive("fileread", [function () {
    return {
        scope: {
            fileread: "="
        },
        link: function (scope, element, attributes) {
            element.bind("change", function (changeEvent) {
                var reader = new FileReader();
                reader.onload = function (loadEvent) {
                    scope.$apply(function () {
                        scope.fileread = loadEvent.target.result;
                    });
                }
                reader.readAsDataURL(changeEvent.target.files[0]);
            });
        }
    }
}]);*/
app.controller('mainController', function ($scope, $http, wave) {


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
        location.href = '#/display';
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
            location.href = '#/display';
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
        } else if (value == "Noisy Heavisine") {
            urlx = "https://raw.githubusercontent.com/rafat/rafat.github.io/master/sites/wavelib/data/noisyheavisine.txt";
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
            location.href = '#/display';
        }, function (response) {
            $scope.data = response.data || "Request failed";
            $scope.status = response.status;
        });
    }

});

app.controller('siteController', function ($scope) {

});

app.controller('displayController', function ($scope, $http, $modal, wave) {
    //console.log(wave.sigLength);
    var lbl = [];
    $scope.MaxIter = 0;
    $scope.selected = {};
    $scope.wdisplays = [];
    for (var i = 0; i < wave.sigLength; ++i) {
        lbl[i] = [i, wave.sigData[i]];
        //console.log(lbl[i]);
    }

    g = new Dygraph(document.getElementById("graph1"),
                    lbl,
                 {
                     legend: 'always',
                     color: '#3399ff',
                     animatedZooms: true,
                     title: 'Input'
                 }
    );
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
        Module._free(outHeap.byteOffset);
        Module._free(filtHeap.byteOffset);
        Module._free(lenHeap.byteOffset);

        $scope.wdisplays = new Array(J + 3);
        $scope.wdisplays[0] = "Input Signal";
        $scope.wdisplays[1] = "Full Decomposition";
        $scope.wdisplays[2] = "Approx at Level " + J;

        for (var i = 3; i < J + 3; i++) {
            $scope.wdisplays[i] = "Details at Level " + (J + 3 - i);
        }

        var lbl = [];
        for (var i = 0; i < wave.outLength; ++i) {
            lbl[i] = [i, wave.output[i]];
        }

        g = new Dygraph(document.getElementById("graph1"),
                    lbl,
                 {
                     legend: 'always',
                     color: '#3399ff',
                     animatedZooms: true,
                     title: 'Full Decomposition'
                 }
        );

        document.getElementById("reportButton").disabled = false;

    }

    $scope.updateGraph = function () {
        //console.log($scope.selected.wdisplay);
        var lbl = [];
        if ($scope.selected.wdisplay == 0) {
            for (var i = 0; i < wave.sigLength; ++i) {
                lbl[i] = [i, wave.sigData[i]];
            }
        } else if ($scope.selected.wdisplay == 1) {
            for (var i = 0; i < wave.outLength; ++i) {
                lbl[i] = [i, wave.output[i]];
            }
        } else if ($scope.selected.wdisplay == 2) {
            for (var i = 0; i < wave.length[0]; ++i) {
                lbl[i] = [i, wave.output[i]];
            }
        } else {
            var k = parseInt($scope.selected.wdisplay) - 2;
            var start_index = 0;
            for (var i = 0; i < k; i++) {
                start_index += wave.length[i];
            }
            var end_index = start_index + wave.length[k];
            for (var i = 0; i < end_index - start_index; ++i) {
                lbl[i] = [i, wave.output[start_index + i]];
            }
        }

        g = new Dygraph(document.getElementById("graph1"),
                    lbl,
                 {
                     legend: 'always',
                     color: '#3399ff',
                     animatedZooms: true,
                     title: $scope.wdisplays[parseInt($scope.selected.wdisplay)]
                 }
        );
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

app.controller("TabsController", function ($scope, $window) {

});