<?php
  print render($form['text']);

  if (user_is_logged_in()) {
    print render($form['estimation']);
    print render($form['submit_button_1']);
    print render($form['submit_button_2']);
  }

  print render($form['table']);

  if (user_is_logged_in()) {
    print drupal_render_children($form);
  }
?>
