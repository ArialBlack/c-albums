<?php print render($form['text']); ?>
<?php print render($form['value']); ?>
<?php print render($form['estimation']); ?>
<?php print render($form['submit_button_1']); ?>
<?php print render($form['submit_button_2']); ?>

<?php print render($form['table']); ?>


<!-- Render any remaining elements, such as hidden inputs (token, form_id, etc). -->
<?php print drupal_render_children($form); ?>