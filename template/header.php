
<!DOCTYPE HTML>
<html>

  <head>
  
    <meta http-equiv="Content-type" content="text/html;charset=UTF-8" />
    <link href="../public/css/leaderboard.css" rel="stylesheet" />
    <style type="text/css"></style>
    
    <?php if(isset($title)): ?>
      <title>LeaderBoard: <?= htmlspecialchars($title) ?></title>
    <?php else: ?>
      <title>LeaderBoard</title>
    <?php endif ?>
  
  </head>
  
  <body>
    <div class="div-head">
      <h3 class="head">
        
        <a class="head-links" href="http://speller-leaderboard.freehostia.com">
          speller Leader Board</a>
          
          <?php if(isset($head)): ?>
            <? echo $head; ?>
          <?php else: ?>    
            <br />
          <?php endif ?>
           
          Harvard College's CS50x from
          
          <a class="head-links" href="http://edx.org">edX.org</a>
          
          <?php if(isset($link)): ?>
            <? echo $link; ?>
          <?php else: ?>
            
          <?php endif ?>
      
      </h3>
    </div>
    
