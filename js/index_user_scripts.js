(function()
{
 "use strict";
 /*
   hook up event handlers 
 */
 function register_event_handlers()
 {

    
     /* button  .uib_w_2 */
    $(document).on("click", ".uib_w_2", function(evt)
    {
        var x = $("#inp1").val().split(/[\s,;\t\r\n]+/);
        wave.sigData = new Float64Array(x.length);
        wave.sigLength = x.length;
        var i;
        for(i = 0;i < x.length;i++) {
            wave.sigData[i] = parseFloat(x[i]);
        }
        alert(wave.sigData[2]);
        displayPage();
    });
    
        /* button  .uib_w_4 */
    $(document).on("click", ".uib_w_4", function(evt)
    {
        var fileinput = document.getElementById('finp1');
        var finp1 = fileinput.files[0];
        var reader = new FileReader();
        
        reader.onload = function(e) {
            var x = reader.result.split(/[\s,;\t\r\n]+/);
            wave.sigData = new Float64Array(x.length);
            wave.sigLength = x.length;
            var i;
            for(i = 0;i < x.length;i++) {
                wave.sigData[i] = parseFloat(x[i]);
            }
            alert(wave.sigData[0]);
            displayPage();
        }
        
        reader.readAsText(finp1);
        
    });
    
    }
 document.addEventListener("app.Ready", register_event_handlers, false);
})();

$(document).ready(function(){
  $('#testsig1').change(function(){
    var value = $(this).val();
    var urlx = null;
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
      
    console.log(urlx);
    $.ajax({
        type:    "GET",
        url:     urlx,
        success: function(data) {
            var x = data.split(/[\s,;\t\r\n]+/);
            wave.sigData = new Float64Array(x.length);
            wave.sigLength = x.length;
            var i;
            for(i = 0;i < x.length;i++) {
                wave.sigData[i] = parseFloat(x[i]);
            }
            console.log(wave.sigLength);
            alert(wave.sigData[0]);
            displayPage();
        },
        error:   function() {
            alert("Signal cannot be loaded. Please try again.")
        }
});  
  });
});