  window.addEventListener('load', Set_value);

    function Refresh(){
      window.location.reload(true);
    }

    function Set_value(){
      document.getElementById("setbutton").addEventListener("click", Refresh); //Set function in not written!
      document.getElementById("pausebutton").addEventListener("click", pause);
      document.getElementById("startbutton").addEventListener("click", start);
      document.getElementById("refreshbutton").addEventListener("click", Refresh);

        var timetake = document.getElementById("time");
        var datafield = document.getElementById("study").value;
        timetake.setAttribute("data-hours", datafield.slice(0,2));
        timetake.setAttribute("data-minutes", datafield.slice(3,5));
        timetake.setAttribute("data-seconds", datafield.slice(6,8));

        var timetake = document.getElementById("time");

        if(timetake.hasAttribute("data-hours")){
        var hours = parseInt(timetake.getAttribute("data-hours"));
        }else{
          var hours = 0;
        }
        if(timetake.hasAttribute("data-minutes")){
        var minutes = parseInt(timetake.getAttribute("data-minutes"));
        }else{
          var minutes = 0;
        }
        if(timetake.hasAttribute("data-seconds")){
        var seconds = parseInt(timetake.getAttribute("data-minutes"));
        }else{
          var seconds = 0;
        }
        if(timetake.hasAttribute("data-start")){
        var paused = timetake.getAttribute("data-start");
        }else{
          paused = false;
        }

        function pause(ispaused) {
          if(ispaused){
            paused = true;
          }
        }  

        var timerStarted = false;
        function start(reset) {
          if(paused){
            paused = false;
          }
          if(!timerStarted){
            CountDown();
            UpdateTimerValue();
          }
        }

        function UpdateTimerValue(){
          var req = new XMLHttpRequest();
          req.open('GET', "/get?value=" + Inseconds, true);
          req.send();
        }

        Inseconds = hours * 3600 + minutes * 60 + seconds;
        function CountDown(){
          timerStarted = true;
          setTimeout(function(){
          if(paused){
            timetake.innerHTML = time;
            Inseconds++;
          }else{
            var hours = Math.floor(Inseconds / 3600);
            var minutes = Math.floor((Inseconds % 3600) / 60);
            var seconds = Math.floor(Inseconds % 60);

            hours = hours < 10 ? '0' + hours : hours; 
            minutes = minutes < 10 ? '0' + minutes : minutes;
            seconds = seconds < 10 ? '0' + seconds : seconds;
            time = (hours + ':' + minutes + ':' + seconds);
            timetake.innerHTML = time;
          }
          Inseconds--;
          if (Inseconds !== -1){
            CountDown();
          }
          }, 1000)
        }
      }