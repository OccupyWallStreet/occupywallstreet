/**
 * @file
 * Processes the FullCalendar options and passes them to the integration.
 */

(function ($) {

Drupal.fullcalendar.plugins.fullcalendar = {
  options: function (fullcalendar, settings) {
    var options = {
      eventClick: function (calEvent, jsEvent, view) {
        if (settings.sameWindow) {
          window.open(calEvent.url, '_self');
        }
        else {
          window.open(calEvent.url);
        }
        return false;
      },
      drop: function (date, allDay, jsEvent, ui) {
        for (var $plugin in Drupal.fullcalendar.plugins) {
          if (Drupal.fullcalendar.plugins.hasOwnProperty($plugin) && $.isFunction(Drupal.fullcalendar.plugins[$plugin].drop)) {
            try {
              Drupal.fullcalendar.plugins[$plugin].drop(date, allDay, jsEvent, ui, this, fullcalendar);
            }
            catch (exception) {
              alert(exception);
            }
          }
        }
      },
      events: function (start, end, callback) {
        // Fetch new items from Views if possible.
        if (fullcalendar.navigate && settings.ajax) {
          var prev_date, next_date, date_argument, argument, fetch_url;

          prev_date = $.fullCalendar.formatDate(start, 'yyyy-MM-dd');
          next_date = $.fullCalendar.formatDate(end, 'yyyy-MM-dd');
          date_argument = prev_date + '--' + next_date;
          argument = settings.args.replace('fullcalendar_browse', date_argument);
          fetch_url = Drupal.settings.basePath + 'fullcalendar/ajax/results/' + settings.view_name + '/' + settings.view_display + '/' + argument;

          $.ajax({
            type: 'GET',
            url: fetch_url,
            dataType: 'json',
            beforeSend: function () {
              // Add a throbber.
              this.progress = $('<div class="ajax-progress ajax-progress-throbber"><div class="throbber">&nbsp;</div></div>');
              $(fullcalendar.dom_id + ' .fc-header-title').after(this.progress);
            },
            success: function (data) {
              if (data.status) {
                // Replace content.
                $(fullcalendar.dom_id + ' .fullcalendar-content').html(data.content);
                fullcalendar.parseEvents(callback);
              }
              // Remove the throbber.
              $(this.progress).remove();
            },
            error: function (xmlhttp) {
              alert(Drupal.t('An HTTP error @status occurred.', {'@status': xmlhttp.status}));
            }
          });
        }
        else {
          fullcalendar.parseEvents(callback);
        }

        if (!fullcalendar.navigate) {
          // Add events from Google Calendar feeds.
          for (var entry in settings.gcal) {
            if (settings.gcal.hasOwnProperty(entry)) {
              $('.fullcalendar', fullcalendar.$calendar).fullCalendar('addEventSource',
                $.fullCalendar.gcalFeed(settings.gcal[entry][0], settings.gcal[entry][1])
              );
            }
          }
        }

        // Set navigate to true which means we've starting clicking on
        // next and previous buttons if we re-enter here again.
        fullcalendar.navigate = true;
      },
      eventDrop: function (event, dayDelta, minuteDelta, allDay, revertFunc) {
        $.post(
          Drupal.settings.basePath + 'fullcalendar/ajax/update/drop/' + event.eid,
          'field=' + event.field + '&entity_type=' + event.entity_type + '&index=' + event.index + '&day_delta=' + dayDelta + '&minute_delta=' + minuteDelta + '&all_day=' + allDay + '&dom_id=' + event.dom_id,
          fullcalendar.update
        );
        return false;
      },
      eventResize: function (event, dayDelta, minuteDelta, revertFunc) {
        $.post(
          Drupal.settings.basePath + 'fullcalendar/ajax/update/resize/' + event.eid,
          'field=' + event.field + '&entity_type=' + event.entity_type + '&index=' + event.index + '&day_delta=' + dayDelta + '&minute_delta=' + minuteDelta + '&dom_id=' + event.dom_id,
          fullcalendar.update
        );
        return false;
      }
    };

    // Merge in our settings.
    $.extend(options, settings.fullcalendar);

    // Pull in overrides from URL.
    if (settings.date) {
      $.extend(options, settings.date);
    }

    return options;
  }
};

}(jQuery));
