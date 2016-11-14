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
          //setInterval(this.loadCommentsFromServer, this.props.pollInterval);
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
                <Comment
                    name={comment.name}
                    subject={comment.subject}
                    comment_body={comment.comment_body}
                    coins_photos={comment.coins_photos}
                    avatar={comment.avatar}
                    comment_author={comment.Author}
                    author_uid={comment.author_uid}
                    post_date={comment.post_date}
                    title={comment.Title}
                    nid={comment.Nid}
                >
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
          //console.log(this.props.subject);
          return (
              <div className="comment">
                <div class="about-user">
                    <a href={'/user/' + this.props.author_uid}><div dangerouslySetInnerHTML={{__html: this.props.avatar}} /></a>
                    <p><a href={'/user/' + this.props.author_uid}>{this.props.comment_author}</a></p>
                    <blockquote dangerouslySetInnerHTML={{__html: this.props.comment_body}} />
                    <p>{this.props.post_date}</p>
                </div>
                <div class="about-coin">
                  <p>about:</p>
                    <a href={'/node/' + this.props.nid}><div dangerouslySetInnerHTML={{__html: this.props.coins_photos[0]}} /></a>
                    <h6><a href={'/node/' + this.props.nid}>{this.props.title}</a></h6>
                </div>
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