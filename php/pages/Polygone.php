<p id="elementTitle">Ajouter un Polygone</p>

<p class="elementDesc">Au moins trois sommets</p>

<form id="formParameters" method="POST" action="./php/controller.php">
    <div class="inputParameter">
        <label for="nbSommets">Sommets</label>   
        <input type="number" id="nbSommets" name="nbSommets" step="1"/>
    </div>
    <div class="inputParameter">
        <input type="submit"  name="setSommets" value="fait"/>
    </div>   
</form>

<?php
//var_dump($_SESSION["nbSommets"]);
if(isset($_SESSION["nbSommets"])){
    echo "<form method='POST' id='formParameters' action='./php/controller.php'>";
    echo "\t";
        echo "<label for='nom'>Nom:</label>";
        echo "<input type='text' id='nom'name='nom' />";
        echo "<br/><br/>";
    for($i = 1; $i <= $_SESSION["nbSommets"]; $i++){ 
        echo "<p class='elementName'>Point ".$i.":</p>";
        echo "<div class='inputParameter'>";
        echo "<label for='".$i."x'>X:</label>";
        echo "<input type='number' id='".$i."x'name='".$i."x' />";
        echo "<br/>";
        echo "\t";
        echo "<label for='".$i."y'>Y:</label>";
        echo "<input type='number' id='".$i."y'name='".$i."y' />";
        echo "<br/>";
        echo "\t";
        echo "<label for='".$i."z'>Z:</label>";
        echo "<input type='number' id='".$i."z'name='".$i."z' />";
        echo "</div>";
        
    }
    echo "<div class='inputParameter'>";
    echo "<input type='submit' value='ajouter' name='addpoly'/>";
    echo "</div>";
    echo "</form>";
}
?>

