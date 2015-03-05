<?php
date_default_timezone_set("Asia/Seoul");
$time = date('His');
if ($time >= "070000" && $time <= "190000") $on = true;
else $on = false;
$fileat = date('H:i:s', filemtime("data/birdview.jpg"));
?>
<html lang="ko">
<head>
  <meta charset="utf-8">
  <title>공터주차장</title>
  <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1">
  <link rel="stylesheet" href="style.css">
  <meta name="apple-mobile-web-app-title" content="공터주차장">
  <link rel="apple-touch-icon" href="icon.png">
</head>
<body>
<header>
  <h1 class="logo">공터주차장</h1>
</header>
<?php if ($on) { ?>
<div>
  <img src="data/birdview.jpg" class="fill" id="birdview">
</div>
<?php } else { ?>
<div class="info">
  <img src="nosvc.png" width="50" height="50">
  <h3>ㅈㅅ합니다!</h3>
  <p>
    현재는 서비스가 제공되지 않습니다.<br>
    이미지는 오전 7시부터 오후 7시까지 제공됩니다.<br>
    그 전이나 후에는 이걸 볼 필요가 없으실꺼에요 :)
  </p>
</div>
<?php } ?>
<div class="help">
  <ul>
    <li>이미지는 5초마다 갱신됩니다. (갱신:<?php echo $fileat; ?>)</li>
    <li>기상에 따라 이미지가 잘 보이지 않을 수도 있습니다.</li>
    <li>"Add to Home Screen" 해 두시면 더 편리하게 이용하실 수 있습니다.</li>
    <li>이미지가 안뜨나요? 카메라에 뭐가 묻었나요? 커피 한잔 쏘시겠다구요?<br>
      E-Mail: <a href="mailto:choo@sungwoo.me">choo@sungwoo.me</a></li>
  </ul>
</div>
<footer>
  &copy; 2015 Sungwoo Choo. All rights reserved.
  <?php if (!$on) { ?>
  <br>
  Thanks to Icons8 for the <a href="http://icons8.com/web-app/6906/Future">Future icon</a>
  <?php } ?>
</footer>
</body>
<?php if ($on) { ?>
<script>
  // Auto reload
  var birdview = document.getElementById("birdview");
  setInterval(function() {
      birdview.src = 'data/birdview.jpg?rand=' + Math.random();
  }, 5000);
</script>
<?php } ?>
<script>
  // Google Analytics
  (function(i,s,o,g,r,a,m){i['GoogleAnalyticsObject']=r;i[r]=i[r]||function(){
  (i[r].q=i[r].q||[]).push(arguments)},i[r].l=1*new Date();a=s.createElement(o),
  m=s.getElementsByTagName(o)[0];a.async=1;a.src=g;m.parentNode.insertBefore(a,m)
  })(window,document,'script','//www.google-analytics.com/analytics.js','ga');
  ga('create', 'UA-44212597-2', 'auto');
  ga('send', 'pageview');
</script>
</html>
