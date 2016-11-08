/**
 * @file
 * Main JS file for react functionality.
 *
 */

(function ($) {

  Drupal.behaviors.react_blocks = {
    attach: function (context) {
      var initCid = null,
          newCid = null,
          toastSubject = null,
          newData = [];

      // A div with some text in it
      var CommentBox = React.createClass({

      loadCommentsFromServer: function() {

        $.ajax({
          url: this.props.url,
          dataType: 'json',
          success: function(data) {
            this.setState({data: data});

            $.each(data, function(i) {
              newData[i] = data[i];
              newCid = newData[i]['cid'];
              toastSubject = newData[i]['subject'];
            });

          }.bind(this),
          error: function(xhr, status, err) {
            console.error(this.props.url, status, err.toString());
          }.bind(this)
        });

        if (newCid != initCid) {
          if (initCid != null) {
            Materialize.toast(toastSubject, 4000);
          }
          initCid = newCid;
          console.log('new comment');
        }

      },

      getInitialState: function() {
        return {data: []};
      },

      componentDidMount: function() {
        this.loadCommentsFromServer();
        //$initString = this.props.subject;
        //console.log(this.state.data);
        setInterval(this.loadCommentsFromServer, this.props.pollInterval);
        //console.log(this.state.data);
      },

      render: function() {
          return (
            <div className="commentBox">
              <CommentList data={this.state.data} />
            </div>
          );
        }
      });

      var CommentList = React.createClass({
        render: function() {
          var commentNodes = this.props.data.map(function (comment) {
            return (
              <Comment name={comment.name} subject={comment.subject}>
                {comment.subject}
              </Comment>
            );
          });
          return (
            <div className="commentList">
              {commentNodes}
            </div>
          );
        }
      });

      var Comment = React.createClass({
        render: function() {
          return (
            <div className="comment">
              {this.props.subject}
            </div>
          );
        }
      });


      // Render our reactComponent
      ReactDOM.render(
        <CommentBox url="/api/comments/last.json" pollInterval={2000} />,
        document.getElementById('recent-comments')
      );

    }
  }

})(jQuery);