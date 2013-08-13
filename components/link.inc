<?php

/**
 * @file
 * Webform Link component
 */

/**
 * Implements _webform_defaults_component().
 */
function _webform_defaults_link() {
  return array(
    'name' => '',
    'form_key' => NULL,
    'pid' => 0,
    'weight' => 0,
    'value' => '',
    'mandatory' => 0,
    'extra' => array(),
  );
}

/**
 * Implements _webform_theme_component().
 */
function _webform_theme_link() {
  return array(
    'webform_display_link' => array(
      'render element' => 'element',
    ),
  );
}

/**
 * Implements _webform_render_component().
 */
function _webform_render_link($component, $value = NULL, $filter = TRUE) {
  $element = array(
    '#type' => 'textfield',
    '#title' => $filter ? _webform_filter_xss($component['name']) : $component['name'],
    '#title_display' => $component['extra']['title_display'] ? $component['extra']['title_display'] : 'before',
    '#default_value' => isset($value) ? $value[0] : '',
    '#required' => $component['mandatory'],
    '#weight' => $component['weight'],
	'#description' => $filter ? _webform_filter_xss($component['description']) : $component['description'],
	'#theme_wrappers' => $format == 'html' ? array('webform_element') : array('webform_element_text'),
    '#translatable' => array('title', 'description'),
    '#element_validate' => array('webform_link_validate'),
  );
  return $element;
}

/**
 * Implements _webform_display_component().
 */
function _webform_display_link($component, $value, $format = 'html') {
  $element = array(
    '#title' => $component['name'],
    '#weight' => $component['weight'],
    '#theme' => 'webform_display_link',
    '#theme_wrappers' => $format == 'html' ? array('webform_element') : array('webform_element_text'),
    '#format' => $format,
    '#value' => $value[0],
    '#translatable' => array('title'),
  );
  return $element;
}

/**
 * Custom theme function for collected link
 */
function theme_webform_display_link($variables) {
  $element = $variables['element'];
  $value = $element['#value'];
  return $value;
}

/**
 * Implements _webform_table_component().
 */
function _webform_table_link($component, $value) {
  return l($value[0], $value[0]);
}

/**
 * Implements _webform_csv_headers_component().
 */
function _webform_csv_headers_link($component, $export_options) {
  $header = array();
  $header[0] = '';
  $header[1] = '';
  $header[2] = $component['name'];
  return $header;
}

/**
 * Implements _webform_csv_data_component().
 */
function _webform_csv_data_link($component, $export_options, $value) {
  return $value[0];
}

/**
 * Form validation handler
 *
 * If a link was submitted, check that the URL is valid.
 */
function webform_link_validate($element, &$form_state) {
  if ($element['#value'] && !valid_url($element['#value'], TRUE)) {
    $message = t('%url is not a valid URL.', array('%url' => l($element['#value'], $element['#value'])));
    form_error($element, $message);
  }
}