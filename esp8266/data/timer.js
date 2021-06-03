// div time
  window.addEventListener('load', TakeTime);
  function TakeTime(){
    var timetake = document.getElementById("time");

    if(timetake.hasAttribute("data-hours")){
    var hours = timetake.getAttribute("data-hours");
    }else{
      var hours = 0;
    }
    if(timetake.hasAttribute("data-minutes")){
    var minutes = timetake.getAttribute("data-minutes");
    }else{
      var minutes = 0;
    }
    if(timetake.hasAttribute("data-seconds")){
    var seconds = timetake.getAttribute("data-minutes");
    }else{
      var seconds = 0;
    }
    if(timetake.hasAttribute("data-start")){
    var paused = timetake.getAttribute("data-start");
    }else{
      paused = false;
    }

    Inseconds = hours * 3600 + minutes * 60 + seconds;

    var button = document.getElementById("pausebutton").addEventListener("click", pause);
    var button = document.getElementById("startbutton").addEventListener("click", start);
    var button = document.getElementById("restartbutton").addEventListener("click", restart);

    function pause(ispaused) {
      if(ispaused){
        paused = true;
      }
    }  
    function start(reset) {
      if(start && paused){
        paused = false;
      }
    }
    function restart(set){
      if(restart){
        var timetake = document.getElementById("time");
        var datafield = document.getElementById("study").value;
        timetake.setAttribute("data-hours", datafield.slice(0,2));
        timetake.setAttribute("data-minutes", datafield.slice(3,5));
        timetake.setAttribute("data-seconds", datafield.slice(6,8));

        //create new time element
        countdown();
      }
    }

    countdown();
    function countdown(){
      setTimeout(function(){
      if(paused){
        timetake.innerHTML = time;
        Inseconds++;
      }else{
        var hours = Math.floor(Inseconds / 3600);
        var minutes = Math.floor((Inseconds % 3600) / 60);
        var seconds = Math.floor(Inseconds % 60);

        hours = hours < 10 ? '0' + hours : hours; //wow if in variablie awesome!
        minutes = minutes < 10 ? '0' + minutes : minutes;
        seconds = seconds < 10 ? '0' + seconds : seconds;
        time = (hours + ':' + minutes + ':' + seconds);
        timetake.innerHTML = time;
      }
      Inseconds--;
      if (Inseconds !== -1){
        countdown();
      }
      }, 1000)
    }

  }

// TimePicker form
