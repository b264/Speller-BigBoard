<?php
/**
*   alert_strings.php  -- alert string variable definitions --
*
*   copyright 2015 Robert Clark(aka ebobtron), et al.
*
*   an expansion of my edX.org 
*   CS50x final project winter/spring 2014  with Launch Code
*************************************************************/
  
$typeString = <<< EOD
    <br /><br />please select the data type you used, if yours is not shown please
    select other.<br /><br /> 
    <a href="javascript:history.go(-1);" class="head-links" style="font-size:1.3em">
    go back and select data type</a><br /><br /><br />
EOD;

$badCookie = <<< EOD
    <br /><br />It appears the cookie has been corrupted, the reason is unclear.
    &nbsp; Your cookie may be from last year.&nbsp; Please continue and choose a
    group.<br /><br /><br />
    Please direct any questions to the
    <a href="mailto:ebobtron@aol.com" class="head-links" style="font-size:1.3em">
    administrator.</a><br />
EOD;

$noCookieSupport = <<< EOD
    <br /><br />The Leader Board has detected that your browser is not supporting
    cookies.<br /><br />The Leader Board uses cookies to track the user's group
    affiliation during file submissions.&nbsp; You may continue and your group will
    default to edX.org&nbsp; Otherwise please enable your cookies or use another
    browser with cookie support.<br /><br />Thanks for using the Leader Board.
    <br /><br />Please direct any questions to the
    <a href="mailto:ebobtron@aol.com" class="head-links" style="font-size:1.3em">
    administrator.</a><br />
EOD;

$dupSubmission = <<< EOD
    <br /><br />The Leader Board has a file as yet untested that matches your current
    submission.&nbsp; The testing and benchmarking programs are not fully automated
    and it may take several hours to see the results on the board.&nbsp; Please hold
    all additional submissions until your current submission reaches the board.<br />
    <br />Thanks<br /><br />Please direct any questions to the
    <a href="mailto:ebobtron@aol.com" class="head-links" style="font-size:1.3em">
    administrator.</a><br />
EOD;

$mysqlConnectionFailed = <<< EOD
    <br><br>It appears the MySQL database server is busy.&nbsp; Sorry please try again.
EOD;

$noRedditProfile = <<< EOD
    <br><br>The Submitter clicked doesn't seem to have a reddit.com id / profile.
EOD;

    // last edit: 01/30/2015  ebt
?>
