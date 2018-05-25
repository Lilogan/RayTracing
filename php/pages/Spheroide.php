<p id="elementTitle">Ajouter un quadrique</p>

<p class="elementDesc">Equation de la forme: <br/> Ax² + By² + Cz²  - 1 = 0:</p>

<form id="formParameters" method="POST" action="./php/controller.php">
    <p class="elementDesc">Début de l'animation</p>

    <div class="inputParameter">
        <label for="A">A:</label>   
        <input type="number" id="A" name='A' step="0.1"/>
    </div>
    <div class="inputParameter">
        <label for="B">B:</label>   
        <input type="number" id="B" name='B' step="0.1"/>
    </div>
    <div class="inputParameter">
        <label for="C">C:</label>   
        <input type="number" id="C" name='C' step="0.1"/>
    </div>
    <div class="inputParameter">
        <label for="Cx">Centre x:</label>   
        <input type="number" id="Cx" name='Cx' step="0.1"/>
    </div>
    <div class="inputParameter">
        <label for="Cy">Centre y:</label>   
        <input type="number" id="Cy" name='Cy' step="0.1"/>
    </div>
    <div class="inputParameter">
        <label for="Cz">Centre z:</label>   
        <input type="number" id="Cz" name='Cz' step="0.1"/>
    </div>
    <div class="inputParameter">
        <select name='materiaux'>
            <?php
               foreach($_SESSION["allMateriaux"] as $mat){
                   echo "<option>".$mat[1]."</option>";
               }
            ?>
        </select>
    </div>

        <p class="elementDesc">Fin de l'animation</p>

    
    <div class="inputParameter">
        <label for="Aend">A:</label>   
        <input type="number" id="Aend" name='Aend' step="0.1"/>
    </div>
    <div class="inputParameter">
        <label for="B">B:</label>   
        <input type="number" id="Bend" name='Bend' step="0.1"/>
    </div>
    <div class="inputParameter">
        <label for="Cend">C:</label>   
        <input type="number" id="Cend" name='Cend' step="0.1"/>
    </div>
    <div class="inputParameter">
        <label for="Cxend">Centre x:</label>   
        <input type="number" id="Cxend" name='Cxend' step="0.1"/>
    </div>
    <div class="inputParameter">
        <label for="Cyend">Centre y:</label>   
        <input type="number" id="Cyend" name='Cyend' step="0.1"/>
    </div>
    <div class="inputParameter">
        <label for="Czend">Centre z:</label>   
        <input type="number" id="Czend" name='Czend' step="0.1"/>
    </div>
    <div class="inputParameter">
        <input type="submit"  name="addSpheroide" value="Ajouter"/>
    </div>

    
</form>



