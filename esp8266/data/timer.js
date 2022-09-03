  window.addEventListener('load', Set_value);

    function Refresh(){
      window.location.reload(true);
    }

    function Set_value(){
      document.getElementById("setbutton").addEventListener("click", setTimer); 
      document.getElementById("pausebutton").addEventListener("click", pause);
      document.getElementById("startbutton").addEventListener("click", start);
      document.getElementById("refreshbutton").addEventListener("click", Refresh);

      function InitializeTimer(type){ //add a datafield choose study/break
        timetake = document.getElementById("time");
        var datafield = document.getElementById(type).value;
        timetake.setAttribute("data-hours", datafield.slice(0,2));
        timetake.setAttribute("data-minutes", datafield.slice(3,5));
        timetake.setAttribute("data-seconds", datafield.slice(6,8));

        timetake = document.getElementById("time");

        if(timetake.hasAttribute("data-hours")){
        hours = parseInt(timetake.getAttribute("data-hours"));
        }else{
          hours = 0;
        }
        if(timetake.hasAttribute("data-minutes")){
        minutes = parseInt(timetake.getAttribute("data-minutes"));
        }else{
          minutes = 0;
        }
        if(timetake.hasAttribute("data-seconds")){
        seconds = parseInt(timetake.getAttribute("data-seconds"));
        }else{
          seconds = 0;
        }
      
        if(timetake.hasAttribute("data-start")){
          paused = timetake.getAttribute("data-start");
        }else{
          paused = false;
        }
        console.log("hours: " + hours + ", minutes: " + minutes + ", seconds:" + seconds);
        Inseconds = hours * 3600 + minutes * 60 + seconds;
        console.log(Inseconds);
      }

        function pause() {
            paused = true;
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

        function UpdateTimerValue(){ //Send Inseconds value to server
          var req = new XMLHttpRequest();
          req.open('GET', "/get?value=" + Inseconds, true);
          req.send();
        }

        function setTimer(){
          pause();
          InitializeTimer("study");
          pause(); 
          UpdateTimerValue();
          
          hours = hours < 10 ? '0' + hours : hours; 
          minutes = minutes < 10 ? '0' + minutes : minutes;
          seconds = seconds < 10 ? '0' + seconds : seconds;
          time = (hours + ':' + minutes + ':' + seconds);
          timetake.innerHTML = time;
        }

        var currentType = "study";
        InitializeTimer(currentType);
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
            breakmark:{ //go here in order to swap break/study times
            //console.log(Inseconds);
            if(Inseconds !== -1){
              CountDown();
            }
            if(Inseconds == -1){
              if(currentType == "study"){
                currentType = "break";
                InitializeTimer(currentType);
                timetake.innerHTML = "Break";
                UpdateTimerValue();
                CountDown();
                break breakmark;
              }
              if(currentType == "break"){
                currentType = "study";
                InitializeTimer(currentType);
                timetake.innerHTML = "Study";
                UpdateTimerValue();
                CountDown();
                break breakmark; 
              }
            }
          }
            }, 1000)
          }
      }