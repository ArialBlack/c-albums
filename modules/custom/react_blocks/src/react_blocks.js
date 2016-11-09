/**
 * @file
 * Main JS file for react functionality.
 *
 */

(function ($) {

  Drupal.behaviors.react_blocks = {
    attach: function (context) {

      //REACT-block LAST 20
      //////////////////////////////////
      // A div with some text in it
      var CommentBox = React.createClass({

        loadCommentsFromServer: function() {

          $.ajax({
            url: this.props.url,
            dataType: 'json',
            success: function(data) {
              this.setState({data: data});
            }.bind(this),
            error: function(xhr, status, err) {
              console.error(this.props.url, status, err.toString());
            }.bind(this)
          });

        },

        getInitialState: function() {
          return {data: []};
        },

        componentDidMount: function() {
          this.loadCommentsFromServer();
          setInterval(this.loadCommentsFromServer, this.props.pollInterval);
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
          <CommentBox url="/api/comments/last-20.json" pollInterval={4000} />,
          document.getElementById('recent-comments')
      );


    }
  }

})(jQuery);