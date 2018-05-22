<p id="elementTitle">Ajouter un Solide</p>

<p class="elementDesc">Au moins trois faces</p>

<form id="formParameters" method="POST" action="./php/controller.php">
    <div class="inputParameter">
        <label for="nbFaces">Faces</label>   
        <input type="number" id="nbFaces" name="nbFaces" step="1"/>
    </div>
    <div class="inputParameter">
        <input type="submit"  name="setFaces" value="fait"/>
    </div>   
</form>

<?php
if(isset($_SESSION["nbFaces"])){
    echo "<form id='formParameters' method='POST' maction='../controller.php'>";
    for($i = 1 ; $i <= $_SESSION["nbFaces"]; $i++){    
        echo "<div class='inputParameters'>";
        echo "<select name='poly".$i."'>";
        if($i % $_SESSION["nbFaces"] == 0){
            $k = 0;
        }else{
            $k++;
        }
        $j = 1;
        foreach($_SESSION["allElements"] as $current){
            if($current[0] == "POLY"){
              
                if($j % $_SESSION["nbFaces"] == $k){
                    echo "<option>".$current[1]."</option>";
                }
                $j++;
            }
            
        }
        echo "</select>";
        echo "<br/>";
        echo "</div>";
    }
    echo "<div class='inputParameter'>";
    echo "<br/>";
    echo "<select name='materiaux'>";
            foreach($_SESSION["allMateriaux"] as $mat){
                echo "<option>".$mat[1]."</option>";
            }
    echo "</select>";
    echo "</div>";
    echo "<div class='inputParameter'>";
    echo "<input type='submit' name='setSolide' value='Ajouter'/>";
    echo "</div>";
    echo "</form>";
}
?>

