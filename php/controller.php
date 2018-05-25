<?php

session_start();
//session_destroy();
function RGB_TO_HSV ($R, $G, $B){
   $HSL = array();
   $var_R = ($R / 255);
   $var_G = ($G / 255);
   $var_B = ($B / 255);
   $var_Min = min($var_R, $var_G, $var_B);
   $var_Max = max($var_R, $var_G, $var_B);
   $del_Max = $var_Max - $var_Min;
   $V = $var_Max;
   if ($del_Max == 0)
   {
      $H = 0;
      $S = 0;
   }
   else
   {
      $S = $del_Max / $var_Max;
      $del_R = ( ( ( $var_Max - $var_R ) / 6 ) + ( $del_Max / 2 ) ) / $del_Max;
      $del_G = ( ( ( $var_Max - $var_G ) / 6 ) + ( $del_Max / 2 ) ) / $del_Max;
      $del_B = ( ( ( $var_Max - $var_B ) / 6 ) + ( $del_Max / 2 ) ) / $del_Max;
      if      ($var_R == $var_Max) $H = $del_B - $del_G;
      else if ($var_G == $var_Max) $H = ( 1 / 3 ) + $del_R - $del_B;
      else if ($var_B == $var_Max) $H = ( 2 / 3 ) + $del_G - $del_R;
      if ($H<0) $H++;
      if ($H>1) $H--;
   }
   $HSL['H'] = $H;
   $HSL['S'] = $S;
   $HSL['V'] = $V;
   return $HSL;
}
function HSV_TO_RGB ($H, $S, $V){
    $RGB = array();
    if($S == 0)
    {
        $R = $G = $B = $V * 255;
    }
    else
    {
        $var_H = $H * 6;
        $var_i = floor( $var_H );
        $var_1 = $V * ( 1 - $S );
        $var_2 = $V * ( 1 - $S * ( $var_H - $var_i ) );
        $var_3 = $V * ( 1 - $S * (1 - ( $var_H - $var_i ) ) );
        if       ($var_i == 0) { $var_R = $V     ; $var_G = $var_3  ; $var_B = $var_1 ; }
        else if  ($var_i == 1) { $var_R = $var_2 ; $var_G = $V      ; $var_B = $var_1 ; }
        else if  ($var_i == 2) { $var_R = $var_1 ; $var_G = $V      ; $var_B = $var_3 ; }
        else if  ($var_i == 3) { $var_R = $var_1 ; $var_G = $var_2  ; $var_B = $V     ; }
        else if  ($var_i == 4) { $var_R = $var_3 ; $var_G = $var_1  ; $var_B = $V     ; }
        else                   { $var_R = $V     ; $var_G = $var_1  ; $var_B = $var_2 ; }
        $R = $var_R * 255;
        $G = $var_G * 255;
        $B = $var_B * 255;
    }
    $RGB['R'] = $R;
    $RGB['G'] = $G;
    $RGB['B'] = $B;
    return $RGB;
}




function setValue($begin, $end, $nbFrame, $curImg){
    return ($begin-$curImg*($begin-$end)/$nbFrame);
}
function colorTransition($r, $rend,$g,$gend,$b,$bend, $nbFrame, $curImg){
    $beginHSV = RGB_TO_HSV($r,$g,$b);
    $endHSV = RGB_TO_HSV($rend, $gend, $bend);

    $hChanged = $beginHSV['H'] + ($endHSV['H'] - $beginHSV['H'])*$curImg/$nbFrame;
    $sChanged = $beginHSV['S'] + ($endHSV['S'] - $beginHSV['S'])*$curImg/$nbFrame;
    $vChanged = $beginHSV['V'] + ($endHSV['V'] - $beginHSV['V'])*$curImg/$nbFrame;
    return HSV_TO_RGB($hChanged, $sChanged,$vChanged);
}
function redirect($lien){
    header("Location: ".$lien);
}

if(filter_input(INPUT_POST, "chooseType", FILTER_SANITIZE_SPECIAL_CHARS)){
    $_SESSION["chosenType"] = filter_input(INPUT_POST, "typePicker", FILTER_SANITIZE_SPECIAL_CHARS);
    echo $_SESSION["chosenType"];
    redirect("../index.php");
}

if(!isset($_SESSION["chosenType"]) || !isset($_SESSION["allElements"]) || !isset($_SESSION["polyName"]) || !isset($_SESSION["allMateriaux"]) || !isset($_SESSION["shownScene"])){
    $_SESSION["chosenType"] = "Lampe";
    $_SESSION["allElements"] = array();
    $_SESSION["polyName"] = array();
    $_SESSION["allMateriaux"] = array();
    $_SESSION["materiauxName"] = array();
    $_SESSION["shownScene"] = "test.jpg";
}

if(filter_input(INPUT_POST, "addSpheroide", FILTER_SANITIZE_SPECIAL_CHARS)){
    $A = filter_input(INPUT_POST, "A", FILTER_SANITIZE_SPECIAL_CHARS);
    $Aend = filter_input(INPUT_POST, "Aend", FILTER_SANITIZE_SPECIAL_CHARS);
    $B = filter_input(INPUT_POST, "B", FILTER_SANITIZE_SPECIAL_CHARS);
    $Bend = filter_input(INPUT_POST, "Bend", FILTER_SANITIZE_SPECIAL_CHARS);
    $C = filter_input(INPUT_POST, "C", FILTER_SANITIZE_SPECIAL_CHARS);
    $Cend = filter_input(INPUT_POST, "Cend", FILTER_SANITIZE_SPECIAL_CHARS);
    $Cx = filter_input(INPUT_POST, "Cx", FILTER_SANITIZE_SPECIAL_CHARS);
    $Cxend = filter_input(INPUT_POST, "Cxend", FILTER_SANITIZE_SPECIAL_CHARS);
    $Cy = filter_input(INPUT_POST, "Cy", FILTER_SANITIZE_SPECIAL_CHARS);
    $Cyend = filter_input(INPUT_POST, "Cyend", FILTER_SANITIZE_SPECIAL_CHARS);
    $Cz = filter_input(INPUT_POST, "Cz", FILTER_SANITIZE_SPECIAL_CHARS);
    $Czend = filter_input(INPUT_POST, "Czend", FILTER_SANITIZE_SPECIAL_CHARS);
    $materialName = filter_input(INPUT_POST, "materiaux", FILTER_SANITIZE_SPECIAL_CHARS);

    if($Aend == NULL){
        $Aend = $A;
    }
    if($Bend == NULL){
        $Bend = $B;
    }
    if($Cend == NULL){
        $Cend = $C;
    }
    if($Cxend == NULL){
        $Cxend = $Cx;
    }
    if($Cyend == NULL){
        $Cyend = $Cy;
    }
    if($Czend == NULL){
        $Czend = $Cz;
    }
    if($A && $B && $C && $Cx!= NULL && $Cy!= NULL && $Cz!= NULL && $materialName != NULL){
        $newQuadra = array();
        //SP A B C Cx Cy Cz
        array_push($newQuadra, "SP");
        array_push($newQuadra, $A);
        array_push($newQuadra, $Aend);
        array_push($newQuadra, $B);
        array_push($newQuadra, $Bend);
        array_push($newQuadra, $C);
        array_push($newQuadra, $Cend);
        array_push($newQuadra, $Cx);
        array_push($newQuadra, $Cxend);
        array_push($newQuadra, $Cy);
        array_push($newQuadra, $Cyend);
        array_push($newQuadra, $Cz);
        array_push($newQuadra, $Czend);
        array_push($newQuadra, $materialName);
        array_push(($_SESSION["allElements"]), $newQuadra);
    }
   redirect("../index.php");
}

if(filter_input(INPUT_POST, "setSommets", FILTER_SANITIZE_SPECIAL_CHARS)){
    $nbSommets = filter_input(INPUT_POST, "nbSommets", FILTER_SANITIZE_SPECIAL_CHARS);
    if($nbSommets >= 3){
        $_SESSION["nbSommets"] = $nbSommets;
    }
    else{
        $_SESSION["nbSommets"] = 3;
    }

    redirect("../index.php");
}

if(filter_input(INPUT_POST, "addpoly", FILTER_SANITIZE_SPECIAL_CHARS)){

    $required = array('x', 'y', 'z');
    $ok = true;
    //check if all form's field are filled
    for($i = 1; $i<=$_SESSION["nbSommets"]; $i++){
        foreach($required as $test){
            if(NULL == filter_input(INPUT_POST, $i.$test, FILTER_SANITIZE_SPECIAL_CHARS)){
                $ok = false;
            }
        }
    }
    $nom = filter_input(INPUT_POST, "nom", FILTER_SANITIZE_SPECIAL_CHARS);
    if($ok == true && $nom && !in_array($nom, $_SESSION["polyName"])){
        $newPoly = array();
        array_push($newPoly, "POLY");
        array_push($newPoly, $nom);
        array_push($_SESSION["polyName"], $nom);

        //POLY nbPoint pt1x pt1y pt1z pt2x pt2y pt2z...
        array_push($newPoly, $_SESSION["nbSommets"]);
        for($i = 1; $i<=$_SESSION["nbSommets"]; $i++){
            $x = filter_input(INPUT_POST, $i."x", FILTER_SANITIZE_SPECIAL_CHARS);
            $y = filter_input(INPUT_POST, $i."y", FILTER_SANITIZE_SPECIAL_CHARS);
            $z = filter_input(INPUT_POST, $i."z", FILTER_SANITIZE_SPECIAL_CHARS);
            array_push($newPoly, $x);
            array_push($newPoly, $y);
            array_push($newPoly, $z);
        }
        array_push($_SESSION["allElements"], $newPoly);
        $_SESSION["nbSommets"] = NULL;
    }

    redirect("../index.php");
}

if(filter_input(INPUT_POST, "addLampe", FILTER_SANITIZE_SPECIAL_CHARS)){
    $newLampe = array();
    array_push($newLampe, "LAMPE");
    //LAMPE X Y Z
    $x = filter_input(INPUT_POST, "X", FILTER_SANITIZE_SPECIAL_CHARS);
    $xend = filter_input(INPUT_POST, "Xend", FILTER_SANITIZE_SPECIAL_CHARS);
    $y = filter_input(INPUT_POST, "Y", FILTER_SANITIZE_SPECIAL_CHARS);
    $yend = filter_input(INPUT_POST, "Yend", FILTER_SANITIZE_SPECIAL_CHARS);
    $z = filter_input(INPUT_POST, "Z", FILTER_SANITIZE_SPECIAL_CHARS);
    $zend = filter_input(INPUT_POST, "Zend", FILTER_SANITIZE_SPECIAL_CHARS);
    $r = filter_input(INPUT_POST, "R", FILTER_SANITIZE_SPECIAL_CHARS);
    $rend = filter_input(INPUT_POST, "Rend", FILTER_SANITIZE_SPECIAL_CHARS);
    $g = filter_input(INPUT_POST, "G", FILTER_SANITIZE_SPECIAL_CHARS);
    $gend = filter_input(INPUT_POST, "Gend", FILTER_SANITIZE_SPECIAL_CHARS);
    $b = filter_input(INPUT_POST, "B", FILTER_SANITIZE_SPECIAL_CHARS);
    $bend = filter_input(INPUT_POST, "Bend", FILTER_SANITIZE_SPECIAL_CHARS);

    if($xend == NULL){
      $xend = $x;
    }
    if($yend == NULL){
        $yend = $y;
    }
    if($zend == NULL){
        $zend = $z;
    }
    if($rend == NULL){
        $rend = $r;
    }
    if($gend == NULL){
        $zgend = $g;
    }
    if($bend == NULL){
        $bend = $b;
    }

    if($x!= NULL && $y!= NULL && $z!= NULL && $r!= NULL && $g!= NULL && $b!= NULL){
        array_push($newLampe, $x);
        array_push($newLampe, $xend);
        array_push($newLampe, $y);
        array_push($newLampe, $yend);
        array_push($newLampe, $z);
        array_push($newLampe, $zend);
        array_push($newLampe, $r);
        array_push($newLampe, $rend);
        array_push($newLampe, $g);
        array_push($newLampe, $gend);
        array_push($newLampe, $b);
        array_push($newLampe, $bend);
        array_push($_SESSION["allElements"], $newLampe);
    }

   redirect("../index.php");
}

if(filter_input(INPUT_POST, "addPlan",FILTER_SANITIZE_SPECIAL_CHARS)){
    $a = filter_input(INPUT_POST, "A",FILTER_SANITIZE_SPECIAL_CHARS);
    $aend = filter_input(INPUT_POST, "Aend",FILTER_SANITIZE_SPECIAL_CHARS);
    $b = filter_input(INPUT_POST, "B",FILTER_SANITIZE_SPECIAL_CHARS);
    $bend = filter_input(INPUT_POST, "Bend",FILTER_SANITIZE_SPECIAL_CHARS);
    $c = filter_input(INPUT_POST, "C",FILTER_SANITIZE_SPECIAL_CHARS);
    $cend = filter_input(INPUT_POST, "Cend",FILTER_SANITIZE_SPECIAL_CHARS);
    $d = filter_input(INPUT_POST, "D",FILTER_SANITIZE_SPECIAL_CHARS);
    $dend = filter_input(INPUT_POST, "Dend",FILTER_SANITIZE_SPECIAL_CHARS);
    $materialName = filter_input(INPUT_POST, "materiaux", FILTER_SANITIZE_SPECIAL_CHARS);

    if($aend == NULL){
        $aend = $a;
    }
    if($bend == NULL){
        $bend = $b;
    }
    if($cend == NULL){
        $cend = $c;
    }
    if($dend == NULL){
        $dend = $z;
    }

    if($a!= NULL && $b!= NULL && $c!= NULL && $d!= NULL && $materialName != NULL){
        //PLAN A B C D
        $plan = array();
        array_push($plan, "PLAN");
        array_push($plan, $a);
        array_push($plan, $aend);
        array_push($plan, $b);
        array_push($plan, $bend);
        array_push($plan, $c);
        array_push($plan, $cend);
        array_push($plan, $d);
        array_push($plan, $dend);
        array_push($plan, $materialName);
        array_push($_SESSION["allElements"], $plan);
    }
    redirect("../index.php");
}

if(filter_input(INPUT_POST, "setFaces", FILTER_SANITIZE_SPECIAL_CHARS)){
    $nbFaces = filter_input(INPUT_POST, "nbFaces", FILTER_SANITIZE_SPECIAL_CHARS);
    if($nbFaces >= 3){
        $_SESSION["nbFaces"] = $nbFaces;
    }
    else{
        $_SESSION["nbFaces"] = 3;
    }

    redirect("../index.php");
}

if(filter_input(INPUT_POST, "setSolide", FILTER_SANITIZE_SPECIAL_CHARS)){
    $ok = true;
    $materialName = filter_input(INPUT_POST, "materiaux", FILTER_SANITIZE_SPECIAL_CHARS);
    for($i = 1; $i<=$_SESSION["nbFaces"]; $i++){
        if(NULL == filter_input(INPUT_POST, "poly".$i, FILTER_SANITIZE_SPECIAL_CHARS)){
            $ok = false;
        }
    }


    if($ok == true && $materialName != NULL){
        $solide = array();
        array_push($solide, "SO");
        array_push($solide, $_SESSION["nbFaces"]);
        for($i = 1; $i<=$_SESSION["nbFaces"]; $i++){
           foreach($_SESSION["allElements"] as $current){
                if($current[0] == "POLY" && $current[1] == filter_input(INPUT_POST, "poly".$i, FILTER_SANITIZE_SPECIAL_CHARS)){
                    array_push($solide, $current);
                }
            }
        }
        array_push($solide, $materialName);
        array_push($_SESSION["allElements"], $solide);
        $_SESSION["nbFaces"] = NULL;
    }
    redirect("../index.php");
}

if(filter_input(INPUT_POST, "execute", FILTER_SANITIZE_SPECIAL_CHARS)){
    $frameRate = filter_input(INPUT_POST, "frameRate", FILTER_SANITIZE_SPECIAL_CHARS);
    $nbImg = filter_input(INPUT_POST, "nbSecondes", FILTER_SANITIZE_SPECIAL_CHARS) * $frameRate;
    $_SESSION["shownScene"] = "output.mp4";
    unlink("./php/output.mp4");
    for($curImg = 1; $curImg <= $nbImg; $curImg++){
        $j = 0;
        $string = NULL;
        $fichier = fopen("../allInfos","w");
        fseek($fichier, 0);
        foreach($_SESSION["allElements"] as $current){
            if($current[0] == "SP"){
                $string = $current[0]."\n".setValue($current[1],$current[2],$nbImg, $curImg)."\n".setValue($current[3],$current[4],$nbImg, $curImg)."\n".setValue($current[5],$current[6],$nbImg, $curImg);
                $string = $string."\n".setValue($current[7],$current[8],$nbImg, $curImg)."\n".setValue($current[9],$current[10],$nbImg, $curImg)."\n".setValue($current[11],$current[12],$nbImg, $curImg);
                foreach($_SESSION["allMateriaux"] as $mat){
                    if($mat[1] == $current[13]){
                      $colors = array();
                      $colors = colorTransition($mat[2],$mat[3],$mat[4],$mat[5],$mat[6],$mat[7], $nbImg,$curImg);
                      $string = $string."\n".$colors['R']."\n".$colors['G']."\n".$colors['B']."\n".$mat[8]."\n".$mat[9]."\n".$mat[10];
                    }
                }
            }
            else if($current[0] == "POLY"){
                $string = $current[0]."\n".$current[1]."\n".$current[2];
                for($i = 1; $i <= $current[2]; $i++){
                    $string = $string."\n".$current[$i*3]."\n".$current[3*$i+1]."\n".$current[3*$i+2];

                }
            }
            else if($current[0] == "LAMPE"){
                $string = $current[0]."\n".setValue($current[1],$current[2],$nbImg,$curImg)."\n".setValue($current[3],$current[4],$nbImg,$curImg)."\n".setValue($current[5],$current[6],$nbImg,$curImg);
                $colors = array();
                $colors = colorTransition($current[7],$current[8],$current[9],$current[10],$current[11],$current[12], $nbImg,$curImg);
                $string = $string."\n".$colors['R']."\n".$colors["G"]."\n".$colors["B"];
            }
            else if($current[0] == "PLAN"){
                $string = $current[0]."\n".setValue($current[1], $current[2],$nbImg, $curImg)."\n".setValue($current[3], $current[4],$nbImg, $curImg)."\n".setValue($current[5], $current[6],$nbImg, $curImg);
                $string = $string."\n".setValue($current[7], $current[8],$nbImg, $curImg);
                foreach($_SESSION["allMateriaux"] as $mat){
                    if($mat[1] == $current[9]){
                      $colors = array();
                      $colors = colorTransition($mat[2],$mat[3],$mat[4],$mat[5],$mat[6],$mat[7], $nbImg,$curImg);
                      $string = $string."\n".$colors['R']."\n".$colors['G']."\n".$colors['B']."\n".$mat[8]."\n".$mat[9]."\n".$mat[10];
                    }
                }

            }
            else if($current[0] == "SO"){
                $string = $current[0]."\n".$current[1];
                for($i = 0; $i < $current[1]; $i++){
                    for($j = 0; $j <= $current[$i+2][2]*3; $j++){
                        $string = $string."\n".$current[$i+2][$j+2];
                    }
                }
                foreach($_SESSION["allMateriaux"] as $mat){
                    if($mat[1] == $current[$current[1]+2]){
                      $colors = array();
                      $colors = colorTransition($mat[2],$mat[3],$mat[4],$mat[5],$mat[6],$mat[7],$nbImg,$curImg);
                      $string = $string."\n".$colors['R']."\n".$colors['G']."\n".$colors['B']."\n".$mat[8]."\n".$mat[9]."\n".$mat[10];
                    }
                }

            }
            if($j == 0){
              fprintf($fichier, "%s",$string);
            }
            else{
                fprintf($fichier, "\r\n%s",$string);
            }
            $j++;

        }
        fprintf($fichier, "\r\nNAME\r\n%s",$curImg.".bmp");
        fclose($fichier);

        //shell_exec(" gcc ../C/test.c ../C/geometric3DTools.c ../C/object.c ../C/bmp.c -lm");
        shell_exec("./a.out");


    }
    $_SESSION["shownScene"] = "./php/1.bmp";
    exec("ffmpeg -framerate ".$frameRate." -i %d.bmp output.mp4");
    redirect("../index.php");
}

if(filter_input(INPUT_POST, "restart", FILTER_SANITIZE_SPECIAL_CHARS)){
    session_destroy();
    redirect("../index.php");
}

if(filter_input(INPUT_POST, "addMateriaux", FILTER_SANITIZE_SPECIAL_CHARS)){
    $nom = filter_input(INPUT_POST, "nom", FILTER_SANITIZE_SPECIAL_CHARS);
    $rouge = filter_input(INPUT_POST, "R", FILTER_SANITIZE_SPECIAL_CHARS);
    $rougeend = filter_input(INPUT_POST, "Rend", FILTER_SANITIZE_SPECIAL_CHARS);
    $vert = filter_input(INPUT_POST, "G", FILTER_SANITIZE_SPECIAL_CHARS);
    $vertend = filter_input(INPUT_POST, "Gend", FILTER_SANITIZE_SPECIAL_CHARS);
    $bleu = filter_input(INPUT_POST, "B", FILTER_SANITIZE_SPECIAL_CHARS);
    $bleuend = filter_input(INPUT_POST, "Bend", FILTER_SANITIZE_SPECIAL_CHARS);
    $reflexion = 0;
    $transparance = 0;
    $refraction = 0;
    if($rougeend == NULL){
      $rougeend = $rouge;
    }
    if($vertend == NULL){
      $vertend = $vert;
    }
    if($bleuend == NULL){
      $bleuend = $bleu;
    }
    if($nom!=NULL && $rouge!=NULL && $vert!=NULL && $bleu!=NULL && !in_array($nom, $_SESSION["materiauxName"])){
        $newMaterial = array();
        array_push($newMaterial, "MAT");
        array_push($newMaterial, $nom);
        array_push($newMaterial, $rouge);
        array_push($newMaterial, $rougeend);
        array_push($newMaterial, $vert);
        array_push($newMaterial, $vertend);
        array_push($newMaterial, $bleu);
        array_push($newMaterial, $bleuend);
        array_push($newMaterial, $reflexion);
        array_push($newMaterial, $transparance);
        array_push($newMaterial, $refraction);
        array_push($_SESSION["allElements"],$newMaterial);
        array_push($_SESSION["allMateriaux"],$newMaterial);
    }
    redirect("../index.php");
}

if(filter_input(INPUT_POST, "showScene", FILTER_SANITIZE_SPECIAL_CHARS)){
    $shownScene = filter_input(INPUT_POST, "scenePicker", FILTER_SANITIZE_SPECIAL_CHARS);
    if($shownScene != "Scènes faites"){
        $_SESSION["shownScene"] = "php/images/".$shownScene.".jpg";
    }
    else{
        echo "dacc";
        $_SESSION["shownScene"] = "test.jpg";
    }
    redirect("../index.php");
}
