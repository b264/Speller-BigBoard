
<?php
/**
 *  alert.php  leader board writen by Robert Clark et al. 2014
 *************************************************************/
    // message string
    $mesString = "no data";
    
    // continue target
    $contarget = "getspeller.php?con=yes";
    
    if(isset($_GET[gsnc])) {
        
        $mesString = "<br><br>" .
                     "The Leader Board has detected that your browser is not supporting " .
                     "cookies.<br><br>The Leader Board uses cookies to track the user " .
                     "group affiliation during file submissions.&nbsp; You may continue " .
                     "and your group will default to edX.org else please enable your " .
                     "cookies or use another browser.<br><br>Thanks for using the Leader ".
                     "Board.<br><br>Please direct any questions to the " .
                     "<a href=\"mailto:ebobtron@aol.com\" class=\"legal-links\" " .
                     "style=\"font-size:16px\">administrator.</a><br>";

    }
    
    // render the page
    
        include("../template/header.php");
        
        include("../template/alertview.php");
        
        include("../template/footer.php");



?>