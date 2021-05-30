    //Study counter
    function Study() {
      var StudyTime = document.getElementById("Study").value;

      var tag_id = document.getElementById('counter');
      tag_id.innerHTML = '<div id="time" data-animate="slide" style="font-size: 80px" data-role="countdown" data-on-alarm="Break()" data-hours="'+ StudyTime[0] + StudyTime[1] +'" data-minutes="'+ StudyTime[3] + StudyTime[4] +'" data-seconds="' + StudyTime[6] + StudyTime[7] + '"></div><br><p>Study</p>';
    }
    //Break counting
    function Break() {
      var BreakTime = document.getElementById("Break").value;

      var tag_id = document.getElementById('counter');
      tag_id.innerHTML = '<div  id="time" data-animate="slide" style="font-size: 80px" data-role="countdown"  data-hours="'+ BreakTime[0] + BreakTime[1] +'" data-minutes="'+ BreakTime[3] + BreakTime[4] +'" data-seconds="' + BreakTime[6] + BreakTime[7] + '"></div><br><p>Break</p>';
    }
    //Stop function
    function Stop(timeleft) {
      var lefthours = Math.floor(timeleft / 3600 );
      var leftminutes = Math.floor((timeleft % 3600)/60);
      var leftseconds = Math.floor(timeleft % 60);

      var tag_id = document.getElementById('counter');
      tag_id.innerHTML = '<div id="time" data-start="false" data-animate="slide" style="font-size: 80px" data-role="countdown" data-on-alarm="Break()" data-hours="'+ lefthours +'" data-minutes="'+ leftminutes +'" data-seconds="' + leftseconds + '"></div><br><p>Study</p>';
    }

// div time
  window.addEventListener('load', TakeTime);
  function TakeTime(){
    var timetake = document.getElementById("test");

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

    var Inseconds = hours * 3600 + minutes * 60 + seconds;


    countdown();
    function countdown(){
      setTimeout(function(){
      var hours = Math.floor(Inseconds / 3600); 
      var minutes = Math.floor((Inseconds % 3600) / 60);
      var seconds = Math.floor(Inseconds % 60);

      hours = hours < 10 ? '0' + hours : hours; //wow if in variablie awesome!
      minutes = minutes < 10 ? '0' + minutes : minutes;
      seconds = seconds < 10 ? '0' + seconds : seconds;
      var time = (hours + ':' + minutes + ':' + seconds);
      timetake.innerHTML = time;

      Inseconds--;
      if (Inseconds !== -1){
        countdown();
      }
      }, 1000)
    }

  }
