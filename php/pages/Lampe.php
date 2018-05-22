<p id="elementTitle">Ajouter une lampe</p>

<p class="elementDesc">position (X,Y,Z)<br/>couleur entre 0 et 255</p>

<form id="formParameters" method="POST" action="./php/controller.php">
    <div class="inputParameter">
        <label for="X">X:</label>   
        <input type="number" id="X" name='X' step="0.1"/>
    </div>
    <div class="inputParameter">
        <label for="Y">Y:</label>
        <input type="number" id="Y" name='Y' step="0.1"/>
    </div>
    <div class="inputParameter">
        <label for="Z">Z:</label>
        <input type="number" id="Z" name='Z' step="0.1"/>
    </div>
    <div class="inputParameter">
        <label for="R">Rouge:</label>
        <input type="number" id="R" name='R' step="1" min="0" max="255"/>
    </div>
    <div class="inputParameter">
        <label for="G">Vert:</label>
        <input type="number" id="G" name='G' step="1" min="0" max="255"/>
    </div>
    <div class="inputParameter">
        <label for="B">Bleu:</label>
        <input type="number" id="B" name='B' step="1" min="0" max="255"/>
    </div>
    
    <div class="inputParameter">
        <input type="submit"  name="addLampe" value="Ajouter"/>
    </div>
</form>



