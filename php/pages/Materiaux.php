<p id="elementTitle">Ajouter un matériaux</p>

<p class="elementDesc">Couleur entre 0 et 255<br/>Rélféxion en pourcentage</p>

<form id="formParameters" method="POST" action="./php/controller.php">
    <div class="inputParameter">
        <label for="nom">Nom:</label>   
        <input type="text" id="nom" name="nom" />
    </div>
    <div class="inputParameter">
        <label for="R">Rouge:</label>   
        <input type="number" id="R" name='R' step="1"/>
    </div>
    <div class="inputParameter">
        <label for="V">Vert:</label>   
        <input type="number" id="V" name='V' step="1"/>
    </div>
    <div class="inputParameter">
        <label for="B">Bleu:</label>   
        <input type="number" id="B" name='B' step="1"/>
    </div>
    <div class="inputParameter">
        <label for="Reflexion">Réflexion:</label>   
        <input type="number" id="Reflexion" name='Reflexion' step="0.1" min="0" max="100"/>
    </div>
    <div class="inputParameter">
        <label for="Transparance">Transparance:</label>   
        <input type="number" id="Transparance" name='Transparance' step="0.1" min="0" max="100"/>
    </div>
    <div class="inputParameter">
        <label for="Refraction">Réfraction:</label>   
        <input type="number" id="Refraction" name='Refraction' step="0.1"/>
    </div>
    
    <div class="inputParameter">
        <input type="submit"  name="addMateriaux" value="Ajouter"/>
    </div>
</form>



